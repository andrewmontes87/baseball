//  
//  IntroToCLanguage
//  Filename: baseball.c
//  Created by Andrew Montes on 8/5/13.
//  Description: function definitions for baseball
//

// baseball.c \\

#include "baseball.h"

// print a fun banner
void print_banner(void)
{
    int a;
    char * b = "BASEBALL";
    for (a=0;a<64;a++)
        putchar('*');
    putchar('\n');
    for (a=0;a<5;a++)
        printf("\n%*s %*s %*s %*s %*s\n",8+a,b,8+a,b,8+a,b,8+a,b,8+a,b);
    putchar('\n');
    for (a=0;a<64;a++)
        putchar('*');
    putchar('\n');
    sleep(1);
}

// load teams from file
void load_teams(FILE * fp, team team[])
{
    int a, b, c;
    char ch;
    printf("\nLoading teams.\n\n");
    for (a=0;a<LEAGUE_SIZE;a++)
    {
        // parse team name
        ch = '\0'; b = 0;
        while (ch != '\n' && b < MAX_STR_LEN)
        {
            fscanf(fp, "%c", &ch);
            team[a].team_name[b] = ch;
            b++;
        }
        team[a].team_name[b-1] = '\0';
        
        // read players
        for (b=0;b<ROSTER_SIZE;b++)
        {
            // parse player name
            ch = '\0'; c = 0;
            while (ch != '\n' && c < MAX_STR_LEN)
            {
                fscanf(fp, "%c", &ch);
                team[a].player[b].player_name[c] = ch;
                c++;
            }
            team[a].player[b].player_name[c-1] = '\0';
            
            // parse player stats
            // POS GP	AB	R	H	2B	3B	HR	RBI	TB	BB	SO	SB  HBP SF
            // 1    2   3   4   5   6   7   8   9   10  11  12  13  14  15
            int pos, gp, ab, r, h, doub, trip, hr, rbi, tb, bb, so, sb, hbp, sf;
            fscanf(fp, "%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d", &pos, &gp, &ab, &r, &h, &doub, &trip, &hr, &rbi, &tb, &bb, &so, &sb, &hbp, &sf);
            team[a].player[b].pos = pos;
            team[a].player[b].gp = gp; 
            team[a].player[b].ab = ab;
            team[a].player[b].r = r; 
            team[a].player[b].h = h;
            team[a].player[b].doub = doub;
            team[a].player[b].trip = trip; 
            team[a].player[b].hr = hr;
            team[a].player[b].rbi = rbi;
            team[a].player[b].tb = tb;
            team[a].player[b].bb = bb; 
            team[a].player[b].so = so; 
            team[a].player[b].sb = sb;
            team[a].player[b].hbp = hbp; 
            team[a].player[b].sf = sf; 
            
            // calculate averages & percentages
            // avg = h / ab
            team[a].player[b].avg = (ab > 0) ? h / ((double)ab) : 0;
            // slg = tb / ab
            team[a].player[b].slg = (ab > 0) ? tb / ((double)ab) : 0;
            // obp = (h + bb + hbp) / (ab + bb + hbp + sf)
            team[a].player[b].obp = (((double)ab) + bb + hbp + sf > 0) ? 
                    (h + bb + hbp) / (((double)ab) + bb + hbp + sf) : 0;
            // ops = obp + slg
            team[a].player[b].ops = (team[a].player[b].slg > 0) ?
                    team[a].player[b].obp + team[a].player[b].slg : 0;
            
            fscanf(fp, "%c", &ch); // skip the newline
        }
        printf("%s loaded.\n", team[a].team_name);
    }
}

// print menu
void print_main_menu(void)
{
    sleep(1);
    printf("\nMENU\n\n"
           "1 - List Teams\n"
           "2 - Print Team Lineup\n"
           "3 - Print Player Stats\n"
           "4 - Print Team Stats\n"
           "5 - Print All Team Stats\n"
           "6 - Sort Team Stats\n"
           "7 - Play Simulated Game\n"
           "8 - Play Simulated Season\n"
           "0 - Quit\n\n");
    printf("Command: ");
}

// get int from stdin
int get_command(int range, char * message)
{
    int input;
    char ch;
    tcflush(STDIN_FILENO, TCIFLUSH);    
    char string[MAX_STR_LEN];
    fgets(string, MAX_STR_LEN, stdin);
    while (sscanf(string, "%d", &input) != 1)
    {
        while ((ch = getchar()) != '\n')
            continue;
        printf("\n%s", message);
        printf("Try again\n\n");
        sleep(1);
        return -1;
    }
    if (input > range || input < 0)
    {
        printf("Out of range.\n%s", message);
        printf("Try again\n\n");
        sleep(1);
        return -1;
    }
    return input;
}

// list team names
void list_teams(team * league)
{
    int a;
    printf("\nTEAM LIST\n");
    for (a=0;a<LEAGUE_SIZE;a++)
        printf("Team %d: %s\n", a+1, league[a].team_name);
    putchar('\n');
}

// translate position int to string
char * get_position(int position)
{
    char * string = " ";
    switch (position)
    {
        case 1: string = "Pitcher"; break;
        case 2: string = "Catcher"; break;
        case 3: string = "First Base"; break;
        case 4: string = "Second Base"; break;
        case 5: string = "Shortstop"; break;
        case 6: string = "Third Base"; break;
        case 7: string = "Left Field"; break;
        case 8: string = "Center Field"; break;
        case 9: string = "Right Field"; break;
    }
    return string;
}

// print team stats to stdout
void print_team_lineup(team * team, int a, bool wait)
{
    int b;
    if (a < 0)
        printf("\nTeam %d: %s\n\tLineup\n\n", a, team->team_name);
    else
        printf("\n%s Lineup\n\n", team->team_name);
    for (b=0;b<ROSTER_SIZE;b++)
    {
        printf("%d, %s: %s\n", b+1, team->player[b].player_name, get_position(team->player[b].pos));    
        printf("\t%d hits in %d at-bats\n", team->player[b].h, team->player[b].ab);
        printf("\t%d home runs, %d RBIs\n", team->player[b].hr, team->player[b].rbi);
        printf("\tBA %.3f, SLG %.3f\n", team->player[b].avg,team->player[b].slg);
        printf("\tOBP %.3f, OPS %.3f\n\n", team->player[b].obp,team->player[b].ops);
        if (wait)
            sleep(1);
    }
}

// driver for print_team_lineup function
void print_team_lineup_driver(team league[])
{
    int input;
    printf("\n\nPRINT LINEUP\n");
    do 
    {
        list_teams(league);
        printf("\nChoose a team:");
        input = get_command(LEAGUE_SIZE, "Enter the number of the team to print.\n0 to exit command.\n");
    } while (input < 0);
    if (input != 0)
        print_team_lineup(&league[input-1], 0, true);
    else
        return;
}

// print all player stats
void print_player_stats(team * team, int player)
{
    
    double temp;
    int a, digits;
    char * string = " ";
    putchar('\n');
    for (a=1,temp=0.0;a<=STATS;a++)
    {
        string = stat_switch(team, a, player);
        temp = team->player[player].temp;
        digits = (a < 15) ? 0 : 3;
        printf("%s %s: %.*f\n", team->player[player].player_name, string, digits, temp);
    }
    putchar('\n');
    sleep(1);
}

// driver for print_player_stats function
void print_player_stats_driver(team league[])
{
    int team, player, a;
    printf("\n\nPRINT PLAYER STATS\n");
    do 
    {
        list_teams(league);
        printf("\nChoose a team:");
        team = get_command(LEAGUE_SIZE, "Enter the number of the team to print.\n0 to exit command.\n");
    } while (team < 0);
    if (team != 0)
    {
        do
        {
            for (a=0;a<ROSTER_SIZE;a++)
                printf("%3d\t%25s\t%15s\n", a+1, league[team-1].player[a].player_name, get_position(league[team-1].player[a].pos));
            printf("\nChoose a player:");
            player = get_command(ROSTER_SIZE, "Enter the number of the team to print.\n0 to exit command.\n");
        } while (player < 0);
        if (player !=0)
            print_player_stats(&league[team-1], player-1);
    }
}

// switches temp field to requested stat for team_stat and sort_stat
char * stat_switch(team * team, int stat, int a)
{
    char * string = " ";
    switch (stat)
    {
            //  GP	AB	R	H	2B	3B	HR	RBI	TB	BB	SO	SB  HBP SF
            //  1    2  3   4   5   6   7   8   9   10  11  12  13  14
        case 1: 
            team->player[a].temp = team->player[a].gp; 
            string = "games played";
            break;
        case 2: 
            team->player[a].temp = team->player[a].ab; 
            string = "at-bats";
            break;
        case 3: 
            team->player[a].temp = team->player[a].r; 
            string = "runs";
            break;
        case 4: 
            team->player[a].temp = team->player[a].h; 
            string = "hits";
            break;
        case 5: 
            team->player[a].temp = team->player[a].doub; 
            string = "doubles";
            break;
        case 6: 
            team->player[a].temp = team->player[a].trip; 
            string = "triples";
            break;
        case 7: 
            team->player[a].temp = team->player[a].hr; 
            string = "home runs";
            break;
        case 8: 
            team->player[a].temp = team->player[a].rbi; 
            string = "runs batted in";
            break;
        case 9: 
            team->player[a].temp = team->player[a].tb;
            string = "total bases";
            break;
        case 10: 
            team->player[a].temp = team->player[a].bb; 
            string = "bases on balls";
            break;
        case 11: 
            team->player[a].temp = team->player[a].so; 
            string = "strike outs";
            break;
        case 12: 
            team->player[a].temp = team->player[a].sb; 
            string = "stolen bases";
            break;
        case 13: 
            team->player[a].temp = team->player[a].hbp; 
            string = "hit by pitch";
            break;
        case 14: 
            team->player[a].temp = team->player[a].sf; 
            string = "sacrifice flys";
            break;
        case 15: 
            team->player[a].temp = team->player[a].avg; 
            string = "batting average";
            break;
        case 16: 
            team->player[a].temp = team->player[a].slg;
            string = "slugging average";
            break;
        case 17: 
            team->player[a].temp = team->player[a].obp; 
            string = "on-base percentage";
            break;
        case 18: 
            team->player[a].temp = team->player[a].ops; 
            string = "on-base percentage + slugging";
            break;
    }
    return string;
}

// calculates player stats and returns the team avg
double team_stat(team * team, int stat, bool write)
{
    double temp;
    int a, digits;
    char * string = " ";
    
    digits = (stat < 15) ? 0 : 3;
    
    for (a=0,temp=0.0;a<ROSTER_SIZE;a++)
    {
        string = stat_switch(team, stat, a);
        temp += team->player[a].temp;
    }
    if (write)
        printf("%s team avg %s: %.*f\n", team->team_name, string, digits, temp/ROSTER_SIZE);
    return temp/ROSTER_SIZE;
}

// driver for team_stat function
void team_stat_driver(team league[])
{
    int input, a;
    printf("\n\nPRINT TEAM STATS\n");
    do 
    {
        list_teams(league);
        printf("\nChoose a team:");
        input = get_command(LEAGUE_SIZE, "Enter the number of the team to print.\n0 to exit command.\n");
    } while (input < 0);
    putchar('\n');
    if (input != 0)
    {
        for (a=1;a<=STATS;a++)
            team_stat(&league[input-1], a, true);
    }
    else
        return;
}

// print all teams stats to stdout
void print_all_stats(team league[])
{
    int a, b;
    for (a=0;a<LEAGUE_SIZE;a++)
    {
        print_team_lineup(&league[a], a+1, false);
        sleep(1);
        for (b=1;b<=STATS;b++)
            team_stat(&league[a], b, true);
        sleep(1);
    }
}

// sort team using linked list, print to stdout
void sort_stat(team * team, int stat)
{
    int a;
    bool not_yet_placed = true;
    char * string = " ";
    
    // create first node, initialize to null
    node * firstnode = NULL;
    
    // build the linked list
    for (a=0;a<ROSTER_SIZE;a++)
    {        
        string = stat_switch(team, stat, a);
        
        // allocate memory for the new node
        node * newnode = malloc(sizeof(node));
        
        // exit error if malloc misfires
        if (newnode == NULL)
            exit(EXIT_FAILURE);  
        
        // point newnode player field to current player
        newnode->player = &team->player[a];
        // point newnode next field to null pointer
        newnode->next = NULL; 
        // reset boolean
        not_yet_placed = true;
        
        // if this is the first time through the loop:
        // the new node becomes first node
        if (firstnode == NULL)
            firstnode = newnode;
        
        // else if (i.e. there are already nodes in the list):
        // check to see if this node belongs at head of line.
        // if the stat is higher than the first item in the
        // line then it should be the new head of the line.
        // point new node's next field at first, set first to
        // new node. new node is shoved in the front of the list.
        else if (newnode->player->temp > firstnode->player->temp)
        {
            newnode->next = firstnode;
            firstnode = newnode;
        }
        // if it doesn't go in front, it must go in middle or end
        else
        {
            node * previousnode = firstnode;
            while (not_yet_placed)
            {
                // if the previous node's next field points to NULL:
                // we are at the end of the line. new node keeps NULL
                // for next, previous node points to new node. new
                // node is attatched to the end of the list.
                if (previousnode->next == NULL)
                {
                    previousnode->next = newnode;
                    not_yet_placed = false;
                }
                // when the relevant stat of the previous node's
                // next's player is less than the stat of the new node's
                // player, shove it in the middle. first point the new
                // node's next at the previous node's next, then
                // point the previous node's next at the new node. 
                // follow this order or you will orphan the end of the 
                // list.
                else if (previousnode->next->player->temp < newnode->player->temp)
                {
                    newnode->next = previousnode->next;
                    previousnode->next = newnode;
                    not_yet_placed = false;
                }
                // if it didn't go in the front, get tacked on to the end,
                // or get shoved in the middle, then it hasn't found its
                // place yet. update previous node to point to its next node
                // for the next iteration of the while loop.
                previousnode = previousnode->next;
            }
        }
    }
    // print sorted lineup
    printf("\n%s lineup\nSorted by %s:\n\n", team->team_name, string);
    node * x = firstnode;
    int digits = (stat < 15) ? 0 : 3;
    for (a=0;a<ROSTER_SIZE;a++)
    {
        printf("%20s\t\t%.*f\n", x->player->player_name, digits, x->player->temp);
        x = x->next;
    }
    fflush(stdout);    
    sleep(1);
    
    // free memory before leaving function
    x = firstnode;
    while (x != NULL)
    {
        node * previouspointer = x;
        x = x->next;
        free(previouspointer);
    }
}

// driver for sort stat function
void sort_stat_driver(team league[])
{
    int team, stat;
    printf("\n\nSORT TEAM STATS\n");
    do 
    {
        list_teams(league);
        printf("\nChoose a team:");
        team = get_command(LEAGUE_SIZE, "Enter the number of the team to print.\n0 to exit command.\n");
    } while (team < 0);
    putchar('\n');
    if (team != 0)
    {
        printf("\nSTATS\n\n"
               "1.  games played\n"
               "2.  at-bats\n"
               "3.  runs\n"
               "4.  hits\n"
               "5.  doubles\n"
               "6.  triples\n"
               "7.  home runs\n"
               "8.  runs batted in\n"
               "9.  total bases\n"
               "10. bases on balls\n"
               "11. strike outs\n"
               "12. stolen bases\n"
               "13. hit by pitch\n"
               "14. sacrifice flys\n"
               "15. batting average\n"
               "16. slugging average\n"
               "17. on-base percentage\n"
               "18. on-base percentage + slugging\n\n");
        do 
        {
            printf("\nChoose a stat:");
            stat = get_command(STATS, "Enter the number of the stat to sort by.\n0 to exit command.\n");
    
        } while (stat < 0);
        putchar('\n');
        if (stat != 0)
            sort_stat(&league[team-1], stat);
        else
            return;
    }
    else
        return;
}

// simulate a game, return name of winner
char * simulated_game(team * away, team * home, bool write)
{
    int a, random1, random2;
    double temp1, temp2, push;
    double diff = 0;
    char * winner = " ";
    
    // only write to stdout if asked to
    if(write)
    {
        putchar('\n');
        for (a=0;a<64;a++)
            putchar('*');
        printf("\n%s at %s\n\n", away->team_name, home->team_name);
    }
    
    // calculate stat differential
    for (a=15;a<=18;a++)
    {
        temp1 = team_stat(away, a, write);
        temp2 = team_stat(home, a, write);
        diff += (temp2 - temp1);
    }
    
    if(write)
        printf("\nRandomizing...\n\n");
    
    // add element of chance
    // seed using the last randomly generated number
    random1 = rand();
    srand(random1);
    random2 = rand();
    srand(random2);
    push = (random1 % 500) / ((double)2000);    // magic voodoo
    if (random2 % 2 == 1)
        diff += push*1.1; // slight weight to home team
    else
        diff -= push;
    
    // determine winner
    if (diff > 0)
    {
        if (write)
            printf("%s beat %s at home\nwith magic number of %.6f\n", home->team_name, away->team_name, diff);
        winner = home->team_name;
    }
    else
    {
        if (write)
            printf("%s beat %s on the road\nwith magic number of %.6f\n", away->team_name, home->team_name, diff*-1);
        winner = away->team_name;
    }
    
    // display if asked
    if(write)
    {
        for (a=0;a<64;a++)
            putchar('*');
        putchar('\n');
        sleep(1);
    }
    return winner;
}

// driver for simulated game function
void simulated_game_driver(team league[])
{
    int home, away;
    char * winner = " ";
    printf("\n\nSIMULATE GAME\n");
    do 
    {
        list_teams(league);
        printf("\nChoose home team:");
        home = get_command(LEAGUE_SIZE, "Enter the number of the team to play at home.\n0 to exit command.\n");
    } while (home < 0);
    if (home != 0)
    {
        do 
        {
            printf("\nChoose away team:");
            away = get_command(LEAGUE_SIZE, "Enter the number of the visiting team.\n0 to exit command.\n");
        } while (away < 0);
        
        if (away != 0)
            winner = simulated_game(&league[away-1], &league[home-1], write);
        else
            return;
    }
}

// simulate 162 games
void simulated_season(team * selected, team league[])
{
    int win = 0, loss = 0;
    char * wins = " ";
    int a = 0, games_played = 0;
    
    while (games_played < 162)
    {
        // play each team in the league
        // repeat at the beginning when you reach the end
        // quit when games played == 162
        for (a = 0; a < LEAGUE_SIZE; a++)
        {
            bool skip = false;
            if (games_played >= 162) break;
            else if (strcmp(selected->team_name, league[a].team_name) == 0) skip = true;
            else if (!skip)
            {
                // home game
                games_played++;
                printf("Game %d: %s at %s\n", games_played, selected->team_name, league[a].team_name);
                if (strcmp(simulated_game(selected, &league[a], false), selected->team_name) == 0)
                {
                    win++;
                    wins = "wins";
                }
                else
                {
                    loss++;
                    wins = "loses";
                }
                printf("\t%s %s\n", selected->team_name, wins);
                // away game
                games_played++;
                printf("Game %d: %s at %s\n", games_played, league[a].team_name, selected->team_name);
                if (strcmp(simulated_game(&league[a], selected, false), selected->team_name) == 0)
                {
                    win++;
                    wins = "wins";
                }
                else
                {
                    loss++; 
                    wins = "loses";
                }
                printf("\t%s %s\n", selected->team_name, wins);
//                // for slow printout
//                if (games_played % 6 == 0)
//                {
//                    putchar('\n');
//                    sleep(1);
//                }
            }
        }

    }
    // print season wrap-up
    putchar('\n');
    for (a=0;a<64;a++)
        putchar('*');
    printf("\n162 simulated games\n");
    printf("%25s  WINS: %d LOSSES: %d\n", selected->team_name, win, loss);
    for (a=0;a<64;a++)
        putchar('*');
    putchar('\n');
    sleep(1);
    return;
}

// driver for simulated season function
void simulated_season_driver(team league[])
{
    int selected;
    printf("\n\nSIMULATE SEASON\n");
    do 
    {
        list_teams(league);
        printf("\nChoose your team:");
        selected = get_command(LEAGUE_SIZE, "Enter the number of the team to play a simulated season.\n0 to exit command.\n");
    } while (selected < 0);
    if (selected != 0)
        simulated_season(&league[selected-1], league);
}
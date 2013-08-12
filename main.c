//  
//  IntroToCLanguage
//  Filename: main.c
//  Created by Andrew Montes on 8/5/13.
//  Description: main driver for baseball
//

// main.c \\

#include "baseball.h"

int main (int argc, char * argv[])
{
    // header banner
    print_banner();
    
    // declare variables
    int input;
    bool quit = false;
    FILE * fp;
    team league[LEAGUE_SIZE];
    srand((unsigned int) time(0));
    
    // open .txt file, exit if error
    // stats from the week of 8/5-9 via baseball-reference.com \\
    
    
	if ((fp = fopen("teams.txt", "r")) == NULL)
    {
        fprintf(stderr,"Can't open \"teams.txt\" file.\n");
        exit(EXIT_FAILURE);
    }
    
    // load teams from file
    load_teams(fp, league);
    
    // close the file, exit if error
    if (fclose(fp) != 0)
    {
        fprintf(stderr,"Error closing file\n");
        exit(EXIT_FAILURE);
    }
    
    // main driver
    while (!quit)
    {
        // get input
        do 
        {
            print_main_menu();
            input = get_command(8, "Type a number between 1 and 8.\n0 to quit.\n");;
        } while (input < 0);

        // try to execute command
        switch (input)
        {
            case 0: quit = true; break;
            case 1: list_teams(league); break;
            case 2: print_team_lineup_driver(league); break;
            case 3: print_player_stats_driver(league); break;
            case 4: team_stat_driver(league); break;
            case 5: print_all_stats(league); break;
            case 6: sort_stat_driver(league); break;
            case 7: simulated_game_driver(league); break;
            case 8: simulated_season_driver(league); break;
        }
    }
    
    printf("\n\nGOODBYE\n\n");

    return 0;
}

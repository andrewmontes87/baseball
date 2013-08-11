//  
//  IntroToCLanguage
//  Filename: baseball.h
//  Created by Andrew Montes on 8/5/13.
//  Description: header for baseball including functions prototypes
//

// baseball.h \\

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <termios.h>
#include <unistd.h> // for *nix systems, including mac
//#include <dos.h>  // for windows systems

#define MAX_STR_LEN 40
#define LEAGUE_SIZE 30
#define ROSTER_SIZE 9
#define STATS 18

typedef struct
{
	char player_name[MAX_STR_LEN + 1];
	int pos, gp, ab, r, h, doub, trip, hr, rbi, tb, bb, so, sb, hbp, sf;
	double avg, slg, obp, ops, temp;
}
player;

typedef struct
{
	char team_name[MAX_STR_LEN + 1];
	player player[ROSTER_SIZE];
}
team;

typedef struct node
{
    player * player;
    struct node * next;
}
node;

void print_banner(void);
void load_teams(FILE * fp, team team[]);
void print_main_menu(void);
int get_command(int range, char * message);
void list_teams(team league[]);
char * get_position(int position);
void print_team_lineup(team * team, int a, bool wait);
void print_team_lineup_driver(team league[]);
void print_player_stats(team * team, int player);
void print_player_stats_driver(team league[]);
char * stat_switch(team * team, int stat, int a);
double team_stat(team * team, int stat, bool write); 
void team_stat_driver(team league[]);
void print_all_stats(team league[]);
void sort_stat(team * team, int stat);
void sort_stat_driver(team league[]);
char * simulated_game(team * away, team * home, bool write);
void simulated_game_driver(team league[]);
void simulated_season(team * selected, team league[]);
void simulated_season_driver(team league[]);
'Baseball' prints and sorts baseball offensive statistics. It also
plays simulated games by comparing lineups. For the purposes of my
app, all teams are in the same league; teams have eight position
players and one pitcher; pitchers have to hit; a simulated season
consists of playing one home game and one away game against a team
and then moving to the next team in the league. Statistics pulled
from baseball-reference.com over the week of 8/5-9.

PLEASE NOTE: this program was built and tested on a Unix-based
operating system. It uses some system-dependent functions that are
included with <unistd.h>. To run on a Windows system, comment out
#include <unistd.h> and uncomment #include <dos.h> in baseball.h.

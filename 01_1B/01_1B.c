/* 
TEAM NUMBER - 1
DATE - 31.07.2023
MEMBERS -
ANANYA BHOWMICK       002111001016
ARIJIT SAHA           002111001118
ROHEENA PAL           002111001096
CHINTAN JANA          002111001115
*/

/*
ASSIGNMENT DETAILS - 
ASSIGNMENT NUMBER 1B
Program to get and set environtment variables using system calls
OUTPUT - Environment variables using getenv() and variables after setenv()
*/

/*
COMPILATION COMMAND -
gcc -o 01_1B 01_1B.c
./01_1B
*/

/*
OUTPUT - 
USER: roheenapal
HOME: /home/roheenapal
HOST: (null)
ARCH: (null)
DISPLAY: :0
PRINTER: (null)
PATH: /home/roheenapal/.cabal/bin:/home/roheenapal/.ghcup/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/usr/lib/wsl/lib:/mnt/c/Program Files/WindowsApps/CanonicalGroupLimited.Ubuntu_2204.2.33.0_x64__79rhkp1fndgsc:/mnt/c/Program Files/Common Files/Oracle/Java/javapath:/mnt/c/Python37/Scripts/:/mnt/c/Python37/:/mnt/c/WINDOWS/system32:/mnt/c/WINDOWS:/mnt/c/WINDOWS/System32/Wbem:/mnt/c/WINDOWS/System32/WindowsPowerShell/v1.0/:/mnt/c/WINDOWS/System32/OpenSSH/:/mnt/c/MinGW/bin:/mnt/c/Program Files/nodejs/:/mnt/c/ProgramData/chocolatey/bin:/mnt/c/Program Files/Git/cmd:/mnt/c/Program Files/Microsoft SQL Server/150/Tools/Binn/:/mnt/c/Program Files/Microsoft SQL Server/Client SDK/ODBC/170/Tools/Binn/:/mnt/c/Program Files/dotnet/:/mnt/c/Program Files/Pandoc/:/mnt/c/Users/HP/AppData/Local/Microsoft/WindowsApps:/mnt/c/Users/HP/AppData/Local/Programs/Microsoft VS Code/bin:/mnt/c/Users/HP/AppData/Roaming/npm:/mnt/c/Program Files/MongoDB/Server/5.0/bin:/mnt/c/Users/HP/.dotnet/tools:/mnt/c/Program Files/heroku/bin:/mnt/c/ghcup/bin:/snap/bin:/home/roheenapal/.local/bin:/home/roheenapal/bin
TEAM1_VAR1: Team1 1st variable
TEAM1_VAR2: Team1 2nd variable
 */


#include <stdio.h>
#include <stdlib.h>

int main() {
    /* Display environment variables using getenv call */
    printf("USER: %s\n", getenv("USER"));
    printf("HOME: %s\n", getenv("HOME"));
    printf("HOST: %s\n", getenv("HOST"));
    printf("ARCH: %s\n", getenv("ARCH"));
    printf("DISPLAY: %s\n", getenv("DISPLAY"));
    printf("PRINTER: %s\n", getenv("PRINTER"));
    printf("PATH: %s\n", getenv("PATH"));

    /* Set two new environment variables */
    const char* environment_var1 = "TEAM1_VAR1";
    const char* environment_val1 = "Team1 1st variable";
    const char* environment_var2 = "TEAM1_VAR2";
    const char* environment_val2 = "Team1 2nd variable";

    /* If the environment variable 1 is not set */
    if (setenv(environment_var1, environment_val1, 1) != 0) {
        perror("setenv");
        return 1;
    }

    /* If the environment variable 2 is not set */
    if (setenv(environment_var2, environment_val2, 1) != 0) {
        perror("setenv");
        return 1;
    }

    /* Printing the environment variables when they are set */
    printf("%s: %s\n", environment_var1, getenv(environment_var1));
    printf("%s: %s\n", environment_var2, getenv(environment_var2));

    return 0;
}

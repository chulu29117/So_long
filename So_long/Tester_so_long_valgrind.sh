#!/bin/bash

# -=-=-=-=-	CLRS -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- #

DEF_COLOR='\033[0;39m'
BLACK='\033[0;30m'
RED='\033[1;91m'
GREEN='\033[1;92m'
YELLOW='\033[0;93m'
BLUE='\033[0;94m'
MAGENTA='\033[0;95m'
CYAN='\033[0;96m'
GRAY='\033[0;90m'
WHITE='\033[0;97m'

# -=-=-=-=-	CLRS -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- #

C=1;

#Function to check erroneous maps ↓
check_error_map() {
    local map_file="$1"
    local EXPECTED_OUTPUT="$2"

    # Run Valgrind and capture its output
    VALGRIND_OUT=$(valgrind --suppressions=suppressions.supp --show-leak-kinds=all \
        --leak-check=full --error-exitcode=1 -- ./so_long "$map_file" 2>&1)
    if echo "$VALGRIND_OUT" | grep -q "All heap blocks were freed"; then
        printf "${GREEN}$C.[MOK]${DEF_COLOR}"
    else
        printf "${RED}$C.[MKO] LEAKS ${DEF_COLOR}"
    fi

    valgrind --suppressions=suppressions.supp --show-leak-kinds=all --leak-check=full \
        --error-exitcode=1 -- ./so_long "$map_file" > test_check.txt

    SO_LONG_EXIT_CODE=$?
    LINE=$(head -n 1 test_check.txt)
    LINE2=$(sed -n '2p' test_check.txt)

    if [ $SO_LONG_EXIT_CODE -eq 139 ]; then
        printf "${RED}[KO] SEGFAULT${DEF_COLOR}\n"
        ((C++))
        rm -rf test_check.txt
        return
    fi

    if [ "$LINE" = "Error" ]; then
        printf "${GREEN}[OK] ${DEF_COLOR}"
        if [ -n "$LINE2" ]; then
            if [ "${#LINE2}" -gt 1 ]; then
                printf "${GRAY}\nExpected output: ${DEF_COLOR} $EXPECTED_OUTPUT \n"
                printf "${GRAY}Your output: ${DEF_COLOR} $LINE2 \n"
            else
                printf "${RED}[KO] You must display an explicit error message${DEF_COLOR}\n"
                printf "${GRAY}Expected output: ${DEF_COLOR} $EXPECTED_OUTPUT \n"
            fi
        else
            printf "${RED}[KO] You must display an explicit error message${DEF_COLOR}\n"
            printf "${GRAY}Expected output: ${DEF_COLOR} $EXPECTED_OUTPUT \n"
        fi
    else
        printf "${RED}[KO] Expected output: Error${DEF_COLOR}\n"
    fi

    ((C++))
    rm -rf test_check.txt
}
#Function to check erroneous maps ↑

#Function to check goods maps ↓
check_valid_map() {
    local map_file="$1"

    VALGRIND_OUT=$(valgrind --suppressions=suppressions.supp --show-leak-kinds=all \
        --leak-check=full --error-exitcode=1 -- ./so_long "$map_file" 2>&1)
    if echo "$VALGRIND_OUT" | grep -q "All heap blocks were freed"; then
        printf "${GREEN}$C.[MOK]${DEF_COLOR}\n"
    else
        printf "${RED}$C.[MKO] LEAKS ${DEF_COLOR}\n"
    fi

    valgrind --suppressions=suppressions.supp --show-leak-kinds=all --leak-check=full \
        --error-exitcode=1 -- ./so_long "$map_file" &
    PID=$!
    sleep 0.35
    ps $PID > /dev/null
    CHECK_ERROR=$?
    if [ $CHECK_ERROR == 0 ]; then
        kill $PID > /dev/null 2>&1
        printf "${GREEN}$C.[OK] ${DEF_COLOR}\n"
    else
        printf "${RED}$C.[KO] ${DEF_COLOR}\n"
    fi

    ((C++))
    rm -rf test_check.txt
}
#Function to check goods maps ↑

rm -rf traces.txt

FILE=$PWD/so_long
TEST=test_check.txt

if [ -f "$FILE" ]; then
    echo -n
else
    printf "${RED}NO EXIST SO_LONG PROGRAM ${DEF_COLOR}\n"
    exit 0
fi

if [ -z "$1" ]; then
    echo -n
fi

# In all these cases your program should print an error and not run the game.
valgrind --suppressions=suppressions.supp --show-leak-kinds=all --leak-check=full --error-exitcode=1 -- ./so_long > test_check.txt  # Test 1

LINE=$(head -n 1 test_check.txt)
LINE2=$(sed -n '2p' test_check.txt)

if [ "$LINE" = "Error" ]; then
    printf "${GREEN}[OK] ${DEF_COLOR}"
    if [ -n "$LINE2" ]; then
        if [ "${#LINE2}" -gt 1 ]; then
            printf "${GRAY}\nExpected output: ${DEF_COLOR} Wrong number of arguments \n"
            printf "${GRAY}Your output: ${DEF_COLOR} $LINE2 \n"
        else
            printf "${RED}[KO] You must display an explicit error message${DEF_COLOR}\n"
            printf "${GRAY}Expected output: ${DEF_COLOR} Wrong number of arguments \n"
        fi
    else
        printf "${RED}[KO] You must display an explicit error message${DEF_COLOR}\n"
        printf "${GRAY}Expected output: ${DEF_COLOR} Wrong number of arguments \n"
    fi
else
    printf "${RED}[KO] Expected output: Error${DEF_COLOR}\n"
fi

((C++))
rm -rf test_check.txt

valgrind --suppressions=suppressions.supp --show-leak-kinds=all --leak-check=full --error-exitcode=1 -- ./so_long invent.ber more argv > test_check.txt  # Test 2

LINE=$(head -n 1 test_check.txt)
LINE2=$(sed -n '2p' test_check.txt)

if [ "$LINE" = "Error" ]; then
    printf "${GREEN}[OK] ${DEF_COLOR}"
    if [ -n "$LINE2" ]; then
        if [ "${#LINE2}" -gt 1 ]; then
            printf "${GRAY}\nExpected output: ${DEF_COLOR} Wrong number of arguments \n"
            printf "${GRAY}Your output: ${DEF_COLOR} $LINE2 \n"
        else
            printf "${RED}[KO] You must display an explicit error message${DEF_COLOR}\n"
            printf "${GRAY}Expected output: ${DEF_COLOR} Wrong number of arguments \n"
        fi
    else
        printf "${RED}[KO] You must display an explicit error message${DEF_COLOR}\n"
        printf "${GRAY}Expected output: ${DEF_COLOR} Wrong number of arguments \n"
    fi
else
    printf "${RED}[KO] Expected output: Error${DEF_COLOR}\n"
fi

((C++))
rm -rf test_check.txt

touch maps_err/permis.ber
chmod 000 maps_err/permis.ber
check_error_map "maps_err/permis.ber" "Permission denied" # Test 3
rm -rf maps_err/permis.ber
check_error_map "invent.ber" "No exist map" # Test 4
check_error_map "maps_err/badextension1.txt" "Bad extension" # Test 5
check_error_map "maps_err/badextension2.ber.txt" "Bad extension" # Test 6
check_error_map "maps_err/badextension3.bber" "Bad extension" # Test 7
check_error_map "maps_err/.ber" "Bad extension" # Test 8
check_error_map "maps_err/no_rectangular.ber" "No rectangular" # Test 9
check_error_map "maps_err/no_rectangular1.ber" "No rectangular" # Test 10
check_error_map "maps_err/no_rectangular2.ber" "No rectangular" # Test 11
check_error_map "maps_err/no_rectangular3.ber" "No rectangular" # Test 12
check_error_map "maps_err/no_rectangular4.ber" "No rectangular" # Test 13
check_error_map "maps_err/no_rectangular5.ber" "No rectangular" # Test 14
check_error_map "maps_err/no_rectangular6.ber" "No rectangular" # Test 15
check_error_map "maps_err/no_rectangular7.ber" "No rectangular" # Test 16
check_error_map "maps_err/no_rectangular8.ber" "No rectangular" # Test 17
check_error_map "maps_err/no_rectangular9.ber" "No rectangular" # Test 18
check_error_map "maps_err/no_player.ber" "No player" # Test 19
check_error_map "maps_err/no_exit.ber" "No exit" # Test 20
check_error_map "maps_err/no_object.ber" "No object" # Test 21
check_error_map "maps_err/duplicate_player.ber" "Duplicate player" # Test 22
check_error_map "maps_err/duplicate_exit.ber" "Duplicate exit" # Test 23
check_error_map "maps_err/no_valid_road.ber" "Duplicate exit" # Test 24
check_error_map "maps_err/no_valid_road1.ber" "Duplicate exit" # Test 25
check_error_map "maps_err/no_valid_road2.ber" "Duplicate exit" # Test 26
check_error_map "maps_err/no_valid_road3.ber" "Duplicate exit" # Test 27
check_error_map "maps_err/no_valid_road4.ber" "Duplicate exit" # Test 28
check_error_map "maps_err/no_valid_road5.ber" "Duplicate exit" # Test 29
check_error_map "maps_err/no_valid_road6.ber" "Duplicate exit" # Test 30
check_error_map "maps_err/no_valid_road7.ber" "Duplicate exit" # Test 31
check_error_map "maps_err/no_valid_road8.ber" "Duplicate exit" # Test 32
check_error_map "maps_err/no_valid_road9.ber" "Duplicate exit" # Test 33
check_error_map "maps_err/no_valid_road10.ber" "Duplicate exit" # Test 34
check_error_map "maps_err/no_walls.ber" "Not surrounded by walls" # Test 35
check_error_map "maps_err/no_walls1.ber" "Not surrounded by walls" # Test 36
check_error_map "maps_err/no_walls2.ber" "Not surrounded by walls" # Test 37
check_error_map "maps_err/no_walls3.ber" "Not surrounded by walls" # Test 38
check_error_map "maps_err/no_walls4.ber" "Not surrounded by walls" # Test 39
check_error_map "maps_err/no_walls5.ber" "Not surrounded by walls" # Test 40
check_error_map "maps_err/no_walls6.ber" "Not surrounded by walls" # Test 41
check_error_map "maps_err/no_walls7.ber" "Not surrounded by walls" # Test 42
check_error_map "maps_err/no_walls8.ber" "Not surrounded by walls" # Test 43
check_error_map "maps_err/no_walls9.ber" "Not surrounded by walls" # Test 44
check_error_map "maps_err/wrong_chars.ber" "Wrong characters" # Test 45
check_error_map "maps_err/wrong_chars1.ber" "Wrong characters" # Test 46
check_error_map "maps_err/wrong_chars2.ber" "Wrong characters" # Test 47
check_error_map "maps_err/wrong_chars3.ber" "Wrong characters" # Test 48
check_error_map "maps_err/wrong_chars4.ber" "Wrong characters" # Test 49
check_error_map "maps_err/wrong_chars5.ber" "Wrong characters" # Test 50
check_error_map "maps_err/no_valid_road11.ber" "Duplicate exit" # Test 51
check_error_map "maps_err/no_valid_road12.ber" "Duplicate exit" # Test 52
check_error_map "maps_err/no_valid_road13.ber" "Duplicate exit" # Test 53
check_error_map "maps_err/no_valid_road14.ber" "Duplicate exit" # Test 54
check_error_map "maps_err/no_valid_road15.ber" "Duplicate exit" # Test 55

printf "\n${CYAN}== Valid map tests ==${DEF_COLOR}\n\n"

check_valid_map "maps_valid/ok.ber"        # Test 56
check_valid_map "maps_valid/ok1.ber"         # Test 57
check_valid_map "maps_valid/ok2.ber"         # Test 58
check_valid_map "maps_valid/ok3.ber"         # Test 59
check_valid_map "maps_valid/ok4.ber"         # Test 60
check_valid_map "maps_valid/ok5.ber"         # Test 61
check_valid_map "maps_valid/ok6.ber"         # Test 62
check_valid_map "maps_valid/ok7orok.ber"     # Test 63
check_valid_map "maps_valid/ok8.ber"         # Test 64
check_valid_map "maps_valid/ok9.ber"         # Test 65
check_valid_map "maps_valid/ok10.ber"        # Test 66
check_valid_map "maps_valid/ok11.ber"        # Test 67
check_valid_map "maps_valid/ok12.ber"        # Test 68
check_valid_map "maps_valid/ok13.ber"        # Test 69
check_valid_map "maps_valid/ok14.ber"        # Test 70
check_valid_map "maps_valid/ok15.ber"        # Test 71

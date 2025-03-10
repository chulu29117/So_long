GREEN='\e[1;32m'
PURPLE='\e[1;35m'
RESET='\033[0m'

echo -e "${PURPLE}
Blocked collectible

${RESET}"
valgrind --leak-check=full --suppressions=./mlx42.supp ./so_long maps/blocked_collect.ber
echo -e "${PURPLE}
----------------------------------------
${RESET}"
echo -e "${PURPLE}
Blocked exit

${RESET}"
valgrind --leak-check=full --suppressions=./mlx42.supp ./so_long maps/blocked_exit.ber
echo -e "${PURPLE}
----------------------------------------
${RESET}"
echo -e  "${PURPLE}
Empty line at end of file

${RESET}"
valgrind --leak-check=full --suppressions=./mlx42.supp ./so_long maps/emptyend.ber
echo -e "${PURPLE}
----------------------------------------
${RESET}"
echo -e "${PURPLE}
Empty line in middle of file

${RESET}"
valgrind --leak-check=full --suppressions=./mlx42.supp ./so_long maps/emptyline.ber
echo -e "${PURPLE}
----------------------------------------
${RESET}"
echo -e "${PURPLE}
Incorrect character in map file

${RESET}"
valgrind --leak-check=full --suppressions=./mlx42.supp ./so_long maps/invalid_char.ber
echo -e "${PURPLE}
----------------------------------------
${RESET}"
echo -e "${PURPLE}
Multiple exits present

${RESET}"
valgrind --leak-check=full --suppressions=./mlx42.supp ./so_long maps/multiple_exit.ber
echo -e "${PURPLE}
----------------------------------------
${RESET}"
echo -e "${PURPLE}
Multiple starts present

${RESET}"
valgrind --leak-check=full --suppressions=./mlx42.supp ./so_long maps/multiple_start.ber
echo -e "${PURPLE}
----------------------------------------
${RESET}"
echo -e "${PURPLE}
No collectibles on map

${RESET}"
valgrind --leak-check=full --suppressions=./mlx42.supp ./so_long maps/no_collect.ber
echo -e "${PURPLE}
----------------------------------------
${RESET}"
echo -e "${PURPLE}
No exit on map

${RESET}"
valgrind --leak-check=full --suppressions=./mlx42.supp ./so_long maps/no_exit.ber
echo -e "${PURPLE}
----------------------------------------
${RESET}"
echo -e "${PURPLE}
Map not rectangular

${RESET}"
valgrind --leak-check=full --suppressions=./mlx42.supp ./so_long maps/no_rect.ber
echo -e "${PURPLE}
----------------------------------------
${RESET}"
echo -e "${PURPLE}
No start on map

${RESET}"
valgrind --leak-check=full --suppressions=./mlx42.supp ./so_long maps/no_start.ber
echo -e "${PURPLE}
Map not enclosed by walls

${RESET}"
valgrind --leak-check=full --suppressions=./mlx42.supp ./so_long maps/open_map.ber
echo -e "${PURPLE}
----------------------------------------
${RESET}"


#!/bin/bash

COLOR_RESET='\E[0m'
WHITE='\E[37m'
GRAY='\E[38m'
BLUE='\E[34m'
CYAN='\E[36m'
YELLOW='\E[33m'
GREEN='\E[32m'
RED='\E[31m'
MAGENTA='\E[35m'

# Lists the subtrees in the repo.
# Adds a remote for that subtree if one doesn't exist. Happens on first execution
# of this file, which should just be when the repo first gets cloned.
# Then it prints out how to push to and pull from the subtree remote repo
ListSubtrees()
{
  subtrees=`git log | grep git-subtree-dir | tr -d ' ' | cut -d ":" -f2 | sort | uniq`

  show_usage=false

  if [ subtrees != "" ]; then
    printf "\n${GREEN}Subtrees in this repo include:\n"
    for (( i=0; i < ${#subtrees[@]}; i++ ))
    do
      if [ "${subtrees[$i]}" == "modules/mot/mot-core" ]; then
        printf "  ${CYAN}${subtrees[$i]}${COLOR_RESET}\n"
        if [ "$(grep "remote \"mot-core\"" ./.git/config)" == "" ]; then
          git remote add mot-core shavian:/home/mnm/git/modules/mot-core.git
          printf "    ${RED}-${COLOR_RESET}Added remote \"mot-core\" with url:\n"
          printf "      \"shavian:/home/mnm/git/modules/mot-core.git\"\n"
          show_usage=true
        fi
        printf "    ${RED}-${COLOR_RESET}To push changes in the subtree directory to the mot-core repo use:\n"
        printf "      git subtree push -P ./${subtrees[$i]} mot-core pcube\n"
        printf "    ${RED}-${COLOR_RESET}To pull changes from the mot-core repo into the subtree use:\n"
        printf "      git subtree pull -P ./${subtrees[$i]} mot-core pcube\n"
      fi
    done
    printf "\n${COLOR_RESET}"
  fi

  if [ $show_usage == true ]; then
    ShowUsage
  fi
}

ShowUsage()
{
  printf "${GREEN}Usage:${COLOR_RESET}\n"
  printf "  Script for running autoreconf and listing git subtrees in the repo\n"
  printf "  ${CYAN}Commands${COLOR_RESET}: (Default is to run autoreconf -i and list subtrees)\n"
  printf "     -s|--subtrees   List subtrees and how-to\n"
  printf "     -h|--help       Show this help message\n"
  printf "  ${CYAN}Examples${COLOR_RESET}:\n"
  printf "     ./boostrap.sh\n"
  printf "     ./boostrap.sh -s\n"
  printf "     ./boostrap.sh -h\n"
  printf "     ./boostrap.sh --subtrees\n"
  printf "     ./boostrap.sh --help\n"
}

main()
{
    case "$1" in
      '-s'|'--subtrees' )
        ListSubtrees
      ;;

      '-h'|'--help' )
        ShowUsage
      ;;

      *)
        autoreconf -i
        ListSubtrees
      ;;
    esac

    exit 0
}

main "$@"

#!/bin/bash

# Author : Pete Vieira
# Email  : Peter.Vieira@jpl.nasa.gov
# Updated: 11/11/2014
# Brief  : This script is for installing the necessary dependencies.

declare -r COLOR_RESET='\E[0m'
declare -r WHITE='\E[37m'
declare -r GRAY='\E[38m'
declare -r BLUE='\E[34m'
declare -r CYAN='\E[36m'
declare -r YELLOW='\E[33m'
declare -r GREEN='\E[32m'
declare -r RED='\E[31m'
declare -r MAGENTA='\E[35m'

declare -r DEPENDENCIES=(
#   Package-manager  Command     Software
    "apt-get"        "install"   "g++"
    "apt-get"        "install"   "cmake"
    "apt-get"        "install"   "libqt4-dev"
)

# Install dependencies defined in list at top
InstallDependencies()
{
    echo -e "\n${RED}CHECKING FOR DEPENDENCIES${COLOR_RESET}"

    # Compute number of dependencies
    declare -l num_dependencies=$((${#DEPENDENCIES[@]} / 3))

    for (( i=0; i < ${num_dependencies}; i++ ))
        do
            # Check if dependency is already installed
            printf "${CYAN}CHECKING FOR ${YELLOW}${DEPENDENCIES[$i*3+2]}${COLOR_RESET}"
            if [ "${DEPENDENCIES[$i*3]}" == "apt-get" ] || [ "${DEPENDENCIES[$i*3]}" == "wget" ] ; then
                local search_result=`dpkg --get-selections | grep -v deinstall | grep ${DEPENDENCIES[$i*3+2]}`
            elif [ "${DEPENDENCIES[$i*3]}" == "pip" ] ; then
                local search_result=`pip list | grep ${DEPENDENCIES[$i*3+2]}`
            else
                echo "\nGot unknown package manager"
                exit 0
            fi
            # If dependency is not installed, ie. search comes up blank, install it
            if [ "$search_result" == '' ] ; then
                echo -e " (${RED}NOT INSTALLED${COLOR_RESET})"
                echo -e "  ${GREEN}INSTALLING ${YELLOW}${DEPENDENCIES[$i*3+2]}${COLOR_RESET}"
                if [ "${DEPENDENCIES[$i*3]}" == "apt-get" ] ; then
                    sudo ${DEPENDENCIES[$i*3]} ${DEPENDENCIES[$i*3+1]} -y ${DEPENDENCIES[$i*3+2]}
                elif [ "${DEPENDENCIES[$i*3]}" == "wget" ] ; then
                    wget -nc ${DEPENDENCIES[$i*3+1]}
                    sudo dpkg -i *${DEPENDENCIES[$i*3+2]}*.deb
                    rm *${DEPENDENCIES[$i*3+2]}*.deb
                else
                    sudo ${DEPENDENCIES[$i*3]} ${DEPENDENCIES[$i*3+1]} ${DEPENDENCIES[$i*3+2]}
                fi
            else
                echo -e " (${GREEN}INSALLED${COLOR_RESET})"
            fi
    done
}

InstallOpenSceneGraph()
{
    printf "${CYAN}Downloading ${YELLOW}OpenSceneGraph-3.2.1${COLOR_RESET}\n"
    wget http://trac.openscenegraph.org/downloads/developer_releases/OpenSceneGraph-3.2.1.zip
    printf "${CYAN}Unzipping ${YELLOW}OpenSceneGraph-3.2.1.zip ${COLOR_RESET}into ${YELLOW}OpenSceneGraph-3.2.1${COLOR_RESET}\n"
    unzip OpenSceneGraph-3.2.1.zip
    printf "${CYAN}Building ${YELLOW}OpenSceneGraph-3.2.1${COLOR_RESET}\n"
    cd OpenSceneGraph-3.2.1
    mkdir build && cd build
    cmake ..
    make
    sudo make install
}

ShowUsage()
{
    echo "Script for installing dependencies"
    echo "Commands: (Default is to install dependencies)"
    echo "   -d|--depends    Install dependencies"
    echo "   -h|--help       Show this help message"
    echo "Examples:"
    echo "   ./install_dependencies.sh"
    echo "   ./install_dependencies.sh -d"
    echo "   ./install_dependencies.sh --help"
}

main()
{
    case "$1" in
	'-d'|'--depends' )
	    InstallDependencies
        InstallOpenSceneGraph
	;;

    '-h'|'--help' )
        ShowUsage
    ;;

	*)
	    InstallDependencies
        InstallOpenSceneGraph
	;;
    esac

    exit 0
}

main "$@"

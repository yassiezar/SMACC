#!/bin/bash

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

GITHUB_USER=robosoft-ai
CATKIN_WORKSPACE_ROOT=`realpath $DIR/..`
GITHUB_TOKEN=$1

#---- TEST GHPAGES LOCALLY VARIABLES------
# uncomment this for local testing and comment the TRAVIS BLOCK
#GITHUB_USER=
#GIT_BRANCH=master
#TRAVIS_REPO_SLUG=smacc
#GITHUB_TOKEN=
#CATKIN_WORKSPACE_ROOT=`pwd`/../..
# ----------- TRAVIS --------------------------
# industrial_ci catkin workspace
#CATKIN_WORKSPACE_ROOT=/root/target_ws
#---------------------------------------
REPO_URL=github.com/robosoft-ai/SMACC_Documentation.git

DIRECTORY=$(cd `dirname $0` && pwd)
echo $DIRECTORY

echo "GH-PAGES"
if [ -n "$GITHUB_TOKEN" ]; then
    ROOT_DIR= `pwd`
    echo "GH - PAGES script working directory: $ROOT_DIR"
    cd "$ROOT_DIR"

    #find / | grep SMACC

    apt-get install -y git

    source $CATKIN_WORKSPACE_ROOT/install/setup.bash
    #source /root/catkin_ws/install/setup.bash

    #remove cloned folder just in case it already existed
    rm -R /tmp/doc

    # This generates a `web` directory containing the website.
    echo "cloning gh-pages"
    git clone https://reelrobotics:$GITHUB_TOKEN@$REPO_URL --branch gh-pages /tmp/doc

    echo "removing specific branch folder from repo clone.."
    cd /tmp/doc
    rm -r $GIT_BRANCH >/dev/null
    mkdir -p $GIT_BRANCH

    echo "cd $CATKIN_WORKSPACE_ROOT"
    ls $CATKIN_WORKSPACE_ROOT/src

    cd $CATKIN_WORKSPACE_ROOT/src/SMACC
    ls

    echo "executing doxygen command"
    doxygen smacc_ci/Doxyfile

    echo "moving result files to branch directory..."
    stat /tmp/doc
    stat /tmp/doc/$GIT_BRANCH
    ls /tmp
    mv /tmp/html /tmp/doc/$GIT_BRANCH
    mv /tmp/latex /tmp/doc/$GIT_BRANCH

    #git init
    #git checkout -b gh-pages
    echo "cd /tmp/doc/$GIT_BRANCH -> directories:"
    ls /tmp/doc
    cd /tmp/doc/$GIT_BRANCH

    git add .
    #git add -f /tmp/doc/index.html
    #echo "------LIST OF FILES ------"
    #find .
    echo "committing new documentation"

    echo `which git`
    echo $(git -c user.name='travis' -c user.email='travis' commit -q -m "gh-pages travis")
    git -c user.name='travis' -c user.email='travis' commit -q -m "gh-pages travis"

    #git diff origin/master..HEAD
    echo "pushing new documentation"
    echo "GITHUB USER: $GITHUB_USER"

    # Make sure to make the output quiet, or else the API token will leak!
    # This works because the API key can replace your password.
    git push -f -v https://reelrobotics:$GITHUB_TOKEN@$REPO_URL gh-pages > pushout.txt
    cat pushout.txt

    # going back to travis build dir
    cd "$ROOT_DIR"
fi

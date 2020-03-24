#!/bin/bash

function startLoop {
  loopVar 1
}

function loopVar {
  if [ $1 -lt $numberOfArguments ]
    then
      nextId=$(( $1+1 ))
      eval "for index$1 in \"\${var$1[@]}\"; do loopVar $nextId; done"
    else
      eval "for index$1 in \"\${var$1[@]}\"; do writeArgumentList; done"
  fi
}

function writeArgumentList {
  for (( j = 1; j <= $numberOfArguments; j++ ))
  do
      eval "printf '%s ' \"\$index$j\""
  done
  printf '\n'
}

function iterateNestedForLoops {
  printf '#'
  for (( i = 1; i <= $#; i++ ))
  do
    eval "declare -a var$i=(\"\${!$i}\")"
    printf '%s ' "$1"
  done
  printf '\n'
  
  numberOfArguments=$#
  startLoop
}
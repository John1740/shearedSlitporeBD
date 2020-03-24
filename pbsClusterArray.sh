#!/bin/bash
. generateArgumentList.sh

if [ $# -ne 2 ] ; then
	echo "expected options: <time HH:MM:SS> <mem e.g. 256mb>"
	exit
fi
set -eu

jobName=configEq_3.56
workDir=/home/sgerloff2/pbs/${jobName}

# param=( 1  )
# arg2L=(1.1 2.2 3.3)
# arg3L=(1e+07 1e+08 1e+09)

# ncFieldAmplitude=( $(seq 0 100 5000) )
shearRate=( $(seq 0 10 500 ) )
# shearRate=( 490 )
# shearRate=( 400 )
# shearRate=( $(seq 0 10 150) $(seq 170 10 230) $(seq 250 10 390) $(seq 410 10 500) )
# ensIndex=( $(seq 0 1 99) )
# ensIndex=( $(seq 0 1 5000) )
ensIndex=( $(seq 0 1 9999) )
# numberOfParticles=( $(seq 50 2 150) )
# numberOfSides=( $(seq 24 1 42) ) 
# outerRingRadius=( $(LANG=en_US seq -f "%g" 3.44 0.01 3.56) )
# outerRingRadius=( 3.56 )
# torqueI=( $(seq 0 1 99) )

# kappa=( $(seq 20 10 50 ) )
# kappa=(30 40 50)
# yukFactor=( $(seq 1 1 10 ) )
# yukFactor=( $(seq 4 1 8 ) )

# outerRingRadius=( $(LANG=en_US seq -f "%g" 3.44 0.01 3.58) )
# numberOfParticles=( $(seq 40 1 70) )

rm -f argumentList.argl
iterateNestedForLoops shearRate[@] ensIndex[@]  >> argumentList.argl


mkdir -p $workDir
cp -r src CMakeLists.txt argumentList.argl $workDir
cd $workDir && cmake -DCMAKE_BUILD_TYPE=RELEASE && make
mv brownianDynamics $workDir/${jobName}
mv argumentList.argl $workDir/${jobName}.argl
cd $workDir
/home/sgerloff2/pbs/submitPBSArrayJob.sh ${jobName} $1 $2

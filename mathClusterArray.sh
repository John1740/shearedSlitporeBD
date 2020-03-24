#!/bin/bash
. generateArgumentList.sh

if [ $# -eq 0 ] ; then
	echo "laufzeit in sekunden angeben"
	exit
fi
set -eu

jobName=distPerParticle_external

# param=( 0 )
# arg2L=(1.1 2.2 3.3)
# arg3L=(1e+07 1e+08 1e+09)

# ncFieldAmplitude=( $(seq 0 100 30000) )
# shearRate=( $(seq 0 10 500) )
shearRate=( 0 160 240 400 )
# ensIndex=( $(seq 0 99) )
# numberOfParticles=( $(seq 50 2 150) )
# numberOfParticles=( 76 78 110 )

rm -f argumentList.argl
iterateNestedForLoops shearRate[@] >> argumentList.argl

src="./src"
workDir=/work/gerloff/jobFiles/workDir
scp -r $src CMakeLists.txt argumentList.argl gerloff@cluster.math.tu-berlin.de:
ssh gerloff@cluster.math.tu-berlin.de 'cd . && cmake -DCMAKE_BUILD_TYPE=RELEASE . && make -C .'
ssh gerloff@cluster.math.tu-berlin.de "mv brownianDynamics $workDir/${jobName} && mv argumentList.argl $workDir/${jobName}.argl"

ssh gerloff@cluster.math.tu-berlin.de "cd $workDir; ./submitArrayJob ${jobName} $1"
ssh gerloff@cluster.math.tu-berlin.de "rm -rf src CMakeLists.txt"

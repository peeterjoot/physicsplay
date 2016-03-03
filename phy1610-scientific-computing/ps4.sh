#!/bin/bash
#PBS -l nodes=1:ppn=8
#PBS -l walltime=0:15:00
#PBS -N peeterj-ants-prof

# Note: submit to queue with:
# 
# cd ; qsub physicsplay/phy1610/ps4.sh
#------------------------
. $HOME/physicsplay/phy1610/scinet.env.ps2_3

ants=$HOME/physicsplay/phy1610/ps3/ants
gprofcmd="gprof --line --no-graph --brief"

cd $SCRATCH

outdir=ants.batch.`date +%F-%T`
mkdir $outdir
cd $outdir

rm -f gmon.out
$ants -t 1000 -n 10000 > ants.out

$gprofcmd $ants > profile.rednode.out

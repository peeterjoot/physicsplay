#!/bin/bash
#PBS -l nodes=4:ppn=8
#PBS -l walltime=0:30:00
#PBS -N peeterj-ps11timeem

# Note: submit to queue with:
# 
# cd ; qsub physicsplay/phy1610-scientific-computing/ps11.sh
#------------------------
phy1610=$HOME/physicsplay/phy1610-scientific-computing
. $phy1610/ps10/setup

cd $SCRATCH || exit 5

outdir=timeem.batch.`date +%F-%T`
mkdir $outdir
cd $outdir || exit 7

# 1-3 min per iteration on a dev node.
$phy1610/ps10/timeAsciiVsNetcdfIO -scaling 2>&1 | tee -a timeem.csv

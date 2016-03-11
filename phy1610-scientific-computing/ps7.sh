#!/bin/bash
#PBS -l nodes=1:ppn=8
#PBS -l walltime=0:15:00
#PBS -N peeterj-grav-time

# Note: submit to queue with:
# 
# cd ; qsub physicsplay/phy1610-scientific-computing/ps7.sh
#------------------------
phy1610=$HOME/physicsplay/phy1610-scientific-computing
. $phy1610/scinet.env.ps7

grav=$phy1610/ps7/grav

cd $SCRATCH

outdir=grav.batch.`date +%F-%T`
mkdir $outdir
cd $outdir

$grav --time > grav.out

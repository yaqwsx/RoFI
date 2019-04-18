#!/bin/bash

input=".videoParams.txt"
INPATH=$(sed -n 1p ${input})
OUTPATH=../data/animation/output.mp4
FRAMERATE=$(sed -n 2p ${input})
DELETE=FALSE

# parse input parameters

while [[ $# -gt 0 ]]
do 
key="$1"

case $key in
	-i|--input)
	INPATH="$2"
	shift
	shift
	;;
	-o|--output)
	OUTPATH="$2"
	shift
	shift
	;;
	-f|--framerate)
	FRAMERATE="$2"
	shift
	shift
	;;
	-d|--delete)
	DELETE=TRUE
	shift
	;;
	-h|--help)
	echo "  -h, --help         Prints help"
	echo "  -i, --input        Directory with pictures to be animated"
	echo "  -o, --output       Output file (path/videoName.mp4)"
	echo "  -f, --framerate    Number of pictures per second"
	echo "  -d, --delete       Delete pictures in the input directory"
	exit 0
	;;
	*)
	echo "Unknown argument $1"
	exit 1
	;;
esac
done

# create vide from simple pictures
ffmpeg -framerate $FRAMERATE -i ${INPATH}/img%04d.png -pix_fmt yuv420p .auxiliary.mp4

# repeat last frame for 1 second 
ffmpeg -i .auxiliary.mp4 -filter_complex "[0]trim=0:1[hold];[0][hold]concat[extended];[extended][0]overlay" $OUTPATH

# remove auxiliary video
rm .auxiliary.mp4

[ "$DELETE" == TRUE ] && rm ${INPATH}/img*.png
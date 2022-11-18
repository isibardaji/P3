#!/bin/bash

#umaxnorm=${1:+-m${1}}
#unorm=${2:+-n${2}}
#upot=${3:+-p${3}}
#uclip1=${4:+--uclip1${4}}
#uclip2=${5:+--uclip2${5}}
# Put here the program (maybe with path)
GETF0="get_pitch $umaxnorm $unorm $upot $clip1"

for fwav in pitch_db/train/*.wav; do
    ff0=${fwav/.wav/.f0}
    echo "$GETF0 $fwav $ff0 ----"
    $GETF0 $fwav $ff0 > /dev/null || (echo "Error in $GETF0 $fwav $ff0"; exit 1)
done

exit 0

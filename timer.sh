#!/bin/sh

for blen in "1024"; do
  echo "[+] Testing for bit length $blen..."
  for nweak in "0002" "0100" "1000"; do 
    echo "  [-] nweak = $nweak..."
    echo -n "" > /tmp/timing_${blen}_${nweak}.txt
    for f in py/generated/spew_WEAK${nweak}_*_${blen}.txt; do
      nkeys="$(echo $f | awk '{split($0,a,"_"); print a[3]}')"
      timeb="$(./tools/bernsteingcd < $f)"
      timep="$(./tools/pelofskegcd < $f)"
      echo "$blen $nweak $nkeys $timeb $timep"
      echo "$nkeys $timeb $timep" >> /tmp/timing_${blen}_${nweak}.txt
    done
    echo "  [-] producing plot..."
    python3 py/plotter.py /tmp/timing_${blen}_${nweak}.txt $blen $nweak
  done
done

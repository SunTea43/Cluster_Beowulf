#!/bin/bash
echo "Executing programs!!";
# (cd Primos; ./launcher.pl)
(cd matrix-multiplication; ./launcher.pl)
(cd matrix-multiplication; ./launcher_just_mpi.pl)
exit

#!bin/bash
mkdir openMpi
cd openMpi

echo"Descargando OpenMpi"
wget https://download.open-mpi.org/release/openMpi/v4.1/openmpi-4.1.3.tar.gz

echo"Descomprimiendo OpenMpi"
tar -xzvf openmpi-4.1.3.tar.gz

echo"Instalacion de build-essential"
sudo apt-get install build-essential

echo"Instalando OpenMPI"
./configure --prefix=$HOME/openMpi
make all
make install
sudo apt-get install openmpi-bin
sudo apt install libopenmpi-dev
export PATH=$PATH:$HOME/openMpi/bin
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$HOME/openMpi/lib
mpicc -v

echo"MPI instalado c:"

echo"Instalacion de NFC common"
sudo apt-get install nfs-common portmap
sudo apt-get install nfs-kernel-server


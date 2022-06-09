#!/bin/bash
sudo apt update;
echo "Actualizado";
sudo apt install -y git;
cd /home/ubuntu/Desktop;
sudo apt install -y make;
sudo apt install -y g++;
sudo apt install -y gcc-11;
git clone https://github.com/ACLXRD/Computacion_Paralela_Distribuida.git;
wget -q https://packages.microsoft.com/keys/microsoft.asc -O- | sudo apt-key add -;
sudo add-apt-repository "deb [arch=amd64] https://packages.microsoft.com/repos/vscode stable main";
sudo apt install code;
code .;
sudo add-apt-repository universe;
sudo apt install -y python3.8-venv;
sudo apt install -y python3-dev;
sudo add-apt-repository -y ppa:ubuntu-toolchain-r/test;	
sudo apt install -y gcc-11;
exit


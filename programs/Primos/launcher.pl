#!/usr/bin/perl

#   Date: 17/02/2022
#   Authors :Andres C. Lopez R., Luis F. Velasquez P., Santiago Perez G.
#   Subjebt: Paralell Computation.
#   Topic: Design of experiments, 
#   automation of execution (average and deviation).


$PATH = `pwd`;
chomp($PATH);
print("Source: ".$PATH. "\n\n");
system "make all";
#system "rm registros/primos.csv";
#Varaible who represents the number of repetitions for each executable file   
$N = 36;
#Vector of executable benchmarks
@ejecutables = ("primos");

#Vector  threads to execute
@threadsN = ("2","4","8","16","28");

@pows = (23);
@number_of_primes = map {2**$_} @pows;
foreach $number (@number_of_primes){
    
    foreach $exe (@ejecutables){
            foreach $thread (@threadsN){
                $file = "$PATH/"."registros/"."$exe".".csv";
                #print($file."\n");
                for ($i = 0; $i < $N; $i++){
                    #print("$PATH/$exe $size $thread \n");
                    system "mpirun -np $thread --hostfile ../../../.mpi_hostfile ./$exe  >> $file $number";
                }
                close $file; 
            }
    }
}
exit(0);

# To make this file executable
#   chmod +x launcher.pl
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
$N = 1+19;
#Vector of executable benchmarks
@ejecutables = ("primes_opnmp_mpi");

#Vector  threads to execute
@threadsN = ("2","4","4","4","4");
@machineN = ("1","1","2","4","7");

@pows = (10..23);
@number_of_primes = map {2**$_} @pows;
foreach $number (@number_of_primes){

    foreach $exe (@ejecutables){
            $j = 0;
            foreach $thread (@threadsN){
                $file = "$PATH/"."registros/"."$exe".".csv";
                print($file."\n");
                for ($i = 0; $i < $N; $i++){
                    #print("$PATH/$exe $size $thread \n");
                    system "mpirun -np @machineN[$j] --hostfile ../../../.mpi_hostfile ./$exe $number $thread  >> $file $number";
                    #print("mpirun -np @machineN[$j] --hostfile ../../../.mpi_hostfile ./$exe $number $thread  >> $file $number\n");
                }
                $j++;
                close $file; 
            }
    }
}
exit(0);

# To make this file executable
#   chmod +x launcher.pl

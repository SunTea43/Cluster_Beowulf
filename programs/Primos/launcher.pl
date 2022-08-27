#!/usr/bin/perl

#   Date: 17/02/2022
#   Authors :Andres C. Lopez R., Luis F. Velasquez P., Santiago Perez G.
#   Subjebt: Paralell Computation.
#   Topic: Design of experiments, 
#   automation of execution (average and deviation).


$PATH = `pwd`;
chomp($PATH);
print("Source: ".$PATH. "\n\n");

#Varaible who represents the number of repetitions for each executable file   
$N = 36;
#Vector of executable benchmarks
@ejecutables = ("primos");

#Vector  threads to execute
@threadsN = ("1","2");

foreach $exe (@ejecutables){
        foreach $thread (@threadsN){
            $file = "$PATH/"."registros/"."$exe"."-$thread".".txt";
            #print($file."\n");
            for ($i = 0; $i < $N; $i++){
                #print("$PATH/$exe $size $thread \n");
                system "$PATH/mpirun -np $thread ../../hostfile ./$exe  >> $file";
            }
            close $file; 
        }
}
exit(0);

# To make this file executable
#   chmod +x launcher.pl
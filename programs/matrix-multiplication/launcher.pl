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
system "rm registros/*.csv";
#Varaible who represents the number of repetitions for each executable file   
$N = 30;
#Vector of executable benchmarks
@ejecutables = ("hybrid-openmp-mm");

#Vector  threads to execute
@threadsN = ("1","2","4");   
@proccesorN = (5..7);

@multiples = (6720,8400,10080);
foreach $number (@multiples){
    foreach $exe (@ejecutables){
        foreach $pro (@proccesorN){
            foreach $thread (@threadsN){
                $file = "$PATH/"."registros/"."$exe".".csv";
                #print($file."\n");
                for ($i = 0; $i < $N; $i++){
                    #print("$PATH/$exe $size $thread \n");
                    #print("mpirun -np $pro --hostfile .mpi_hostfile ./$exe $number $thread >> $file \n");
                    system "mpirun -np $pro --hostfile .mpi_hostfile ./$exe $number $thread >> $file \n";
		}
                close $file; 
            }
        }
    }
}
exit(0);

# To make this file executable
#   chmod +x launcher.pl

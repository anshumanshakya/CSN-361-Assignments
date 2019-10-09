
#——-Event scheduler object creation——–#
set ns [new Simulator]

#———-creating nam objects—————-#

set nf [open problem4.nam w]
$ns namtrace-all $nf

#———- Creating Network—————-#

puts "Enter number of nodes in ring topology: "
gets stdin totalNodes

for {set i 0} {$i < $totalNodes} {incr i} {
set node_($i) [$ns node]
}

for {set i 0} {$i < $totalNodes} {incr i} {
$node_($i) shape hexagon
$node_($i) color green
}

for {set i 0} {$i < $totalNodes} {incr i} {
$ns duplex-link $node_($i) $node_([expr ($i+1)%$totalNodes]) 1Mb 10ms DropTail
}

puts "Enter number of nodes to be connected "
gets stdin k
#————Data Transfer between Nodes—————-#

for {set i 0} {$i < $k} {incr i} {
puts "Enter pairs of nodes : "
gets stdin node1
gets stdin node2

#Create a TCP agent and attach it to node n0
set tcp($i) [new Agent/TCP]
$ns attach-agent $node_($node1) $tcp($i)
#Create a TCP Sink agent (a traffic sink) for TCP and attach it to node n3
set sink($i) [new Agent/TCPSink]
$ns attach-agent $node_($node2) $sink($i)
#Connect the traffic sources with the traffic sink
$ns connect $tcp($i) $sink($i)
}


# Setting flow color
for {set i 0} {$i < $k} {incr i} {
$tcp($i) set fid_ ($i)
}

# Create a FTP and attach it to tcp
for {set i 0} {$i < $k} {incr i} {
set ftp($i) [new Application/FTP]
$ftp($i) attach-agent $tcp($i)
}

#———finish procedure——–#

proc finish {} {
global ns nf 
$ns flush-trace
close $nf
puts "running nam…"
exec nam problem4.nam &
exit 0
}

# data packet generation starting time
for {set i 0} {$i < $k} {incr i} {
set start "ftp"
set temp "$"
append start ($i)
append start " start"
append temp $start
$ns at 0.5 $temp
}

# data packet generation ending time
for {set i 0} {$i < $k} {incr i} {
set end "ftp"
set temp "$"
append end ($i)
append end " stop"
append temp $end
$ns at 5.0 $temp
}

#Calling finish procedure
$ns at 6.0 "finish"
$ns run
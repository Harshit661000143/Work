#!/usr/bin/perl
open($files,"$ARGV[0]") or die("Can't locate file $ARGV[0]\n");
open(NEWDAT,">Data_File") or die("Can't locate file Data File\n");
while($entry=<$files>)
{
        chomp($entry);
        if($entry=~/\:/)
{
        @items=split(/:/,$entry);
       $matrix=$items[0];
        @items1=split(/=/,$entry);
        $ttime=$items1[1];
        print NEWDAT "$matrix\t$ttime\n";

#        print "$matrix\t$ttime\n";
}
}


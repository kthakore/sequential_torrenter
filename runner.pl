use strict;
use warnings;

my $D; 

my $d = $ARGV[0] || 'torrents';

opendir( $D, "$d") || die "Can't open dir $d: $!\n";
my @list = readdir($D);
closedir($D);

foreach my $file ( @list )
{
    unless($file eq '\.' || $file eq '\.\.' ){
             warn $file;

        if ( $file =~ 'torrent' ){
   
                `./sc '$d/$file'`; 
           }


    }
}
    

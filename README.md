# Archiver
File Archiver written in C


written in c, compiled with gcc

Format:
four different command line flags:
  archiver -a archive.name file1 file2 file3 ... fileN
    Creates archive file called archive.name made up of files 1-N 
  archiver -u archive.name
    Unpacks archive file
  archiver -l archive.name
    for every file in the archive it lists the name and the size
  archiver -v archive.name file1 file2 file3 ... fileN
    verifies the archive contains files 1-N
    if the archives differ, prints number of bytes it is missing
    



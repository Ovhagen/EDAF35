COMPILER = gcc
FILESYSTEM_FILES = rawdisk.c ssfs.c fs_support.c
FORMAT_FILES = fs_support.c rawdisk.c format_myfs.c
INFO_FILES = fs_support.c rawdisk.c info_myfs.c

build: $(FILESYSTEM_FILES)
	$(COMPILER) $(FILESYSTEM_FILES) -o ssfs `pkg-config fuse --cflags --libs`
	@echo 'To Mount: ./ssfs -f [mount point]'
	@echo 'For more debug information, run with -d as well.'

preproc: $(FILESYSTEM_FILES)
		$(COMPILER) $(FILESYSTEM_FILES) -E `pkg-config fuse --cflags --libs` > ssfs.text

tools: $(FORMAT_FILES) $(INFO_FILES)
	$(COMPILER) $(FORMAT_FILES) -o format_myfs
	$(COMPILER) $(INFO_FILES) -o info_myfs

clean:
	rm ssfs format_myfs info_myfs

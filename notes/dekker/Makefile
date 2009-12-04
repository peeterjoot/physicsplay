all : dekker dekker_mfence dekker_lfence dekker_sfence dekker_sched

dekker: dekker.c
	g++ dekker.c -o $@ -lpthread

dekker_mfence: dekker.c
	g++ dekker.c -o $@ -lpthread -DUSE_MFENCE

dekker_sfence: dekker.c
	g++ dekker.c -o $@ -lpthread -DUSE_SFENCE

dekker_lfence: dekker.c
	g++ dekker.c -o $@ -lpthread -DUSE_LFENCE

dekker_sched: dekker.c
	g++ dekker.c -o $@ -lpthread -DUSE_SCHED_FENCE

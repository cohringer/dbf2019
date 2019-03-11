#pseudocode

while on

#init cond variables "undone"

	while bombdrop==1
		for i
			drop
			i+1
		if i=6
			reset
		#pins 1-6 on servo driver for bombs
	while wingfold==1
		while high && limit==0
			if servo locked
				unlock
				#(servo driver pin 10/11 LR)
				wait
			actuate wing fold servo 
			#(servo driver pin 8/9 LR)
			read in limit #(2-5 on Arduino)
			if limit
				lock
				wingfold==0
				limit==1
		while low && limit==1;
			if servo locked
				unlock
				wait
			actuate wing unfold
			read in limit
			if limit
				lock 
				wingfold==0
				limit==0




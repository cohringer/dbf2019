#pseudocode

while on 

//init cond variables "undone"
read input from nick
sets bombdrop or wingfold=1
	while bombdrop==1
		for i
			drop
			i+1
		if i=6
			reset
			set bomb drop to 0
		#pins 1-6 on servo driver for bombs
	while wingfold==1 && failsafe=1

	#Define limits as LeftLow=LL LeftHigh=LH RightLow=RL RightHigh=RH 
	#limitF=limitFold, limitU=limitunfold 
		while high && limitH==0 #potential bug with limitH and limitU
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
				limitH==1 
		while low && limitU==0;
			if servo locked
				unlock
				wait
			actuate wing unfold
			read in limit
			if limit
				lock 
				wingfold==0
				limitU==0

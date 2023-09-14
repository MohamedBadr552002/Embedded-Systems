RESET		;CPU entry point
			mov		r0,#5
			bl		main
		
		
main 
			bl		subtract	
			bl 		termenation
		
subtract
			sub		r0,r0,#1
			cmp		r0,#0
			bnq		subtract
			mov 	cp.bl			;== bx	bl
			
			
termenation  ;End of program			
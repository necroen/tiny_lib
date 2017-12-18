TH_TENSOR_APPLY2_D(TYPE1, TENSOR1, TYPE2, TENSOR2, DIM, CODE)
DIM = -1 变成
TH_TENSOR_APPLY2(TYPE1, TENSOR1, TYPE2, TENSOR2, CODE)


void THIntTensor_add(THIntTensor *r_, THIntTensor *t, int value)
{
  	THIntTensor_resizeAs(r_, t);

	{ 
	int TH_TENSOR_APPLY_hasFinished = 0; 
	int TH_TENSOR_dim_index = 0; 

	// __TH_TENSOR_APPLYX_PREAMBLE(TYPE, TENSOR, DIM, ALLOW_CONTIGUOUS)
	// DIM = -1   ALLOW_CONTIGUOUS = 1
	printf("1begin");  
	int *r__data = NULL; 
	int *r__counter = NULL, *r__sizes = NULL, *r__strides = NULL, *r__dimOffset = NULL; 
	int r__stride = 0, r__size = 0, r__dim = 0, r__i, r__n; 
	int r__contiguous = 1 && -1 < 0;  // ALLOW_CONTIGUOUS && DIM < 0; 
	r__n = (r_->nDimension ? 1 : 0);  //

	for(r__i = 0; r__i < r_->nDimension; r__i++) 
		r__n *= r_->size[r__i];  //

	if(r_->nDimension == 0) 
		TH_TENSOR_APPLY_hasFinished = 1; 
  	else 
	{ 
		r__data = r_->storage->data+r_->storageOffset; // 数据指针
		r__size = 1; 
		r__stride = 1; 
  		for(r__i = r_->nDimension-1; r__i >= 0; r__i--)  // 从最右维开始，r__i标记维度
		{ 
			if(r_->size[r__i] != 1)  // 跟 isContiguous 函数一样
			{ 
				if(r_->stride[r__i] == r__size && r__i != -1) 
					r__size *= r_->size[r__i]; 
				else
				{  r__contiguous = 0; break;  }  // 判定出 内存层面不连续
			} 
		} 
  		
  		if (!r__contiguous) // 如果不连续
		{ 	/* Find the dimension of contiguous sections */
			r__dim = 1; 
			for(r__i = r_->nDimension-2; r__i >= 0; r__i--)
			{ 
				if(r_->stride[r__i] != r_->stride[r__i+1] * r_->size[r__i+1] || r__i == -1 || r__i+1 == -1) 
					r__dim++; 
			} 

			/* Allocate an array of 3*dim elements, where dim is the number of contiguous sections */
			r__counter = (int*)THAlloc(sizeof(int)*(3*r__dim)); 
			r__sizes = r__counter + r__dim; 
			r__strides = r__counter + 2*r__dim; 
			TH_TENSOR_dim_index = r__dim-1; 
			r__dimOffset = (-1 == r_->nDimension-1) ? &r__i : &r__counter[-1]; 
			r__sizes[TH_TENSOR_dim_index] = r_->size[r_->nDimension-1]; 
			r__strides[TH_TENSOR_dim_index] = r_->stride[r_->nDimension-1]; 

			/* TENSOR##_counter tracks where we are in the storage. The offset into the */             
      		/* storage is given by storage_offset + (i * j), where i is the stride */                  
      		/* vector and j is tensor_counter vector. This sets the starting position for the loop. */ 
			for(r__i = r__dim-1; r__i >= 0; --r__i) 
				{ r__counter[r__i] = 0; } 

			for(r__i = r_->nDimension-2; r__i >= 0; --r__i) 
			{ 
				if (r_->stride[r__i] == r_->stride[r__i+1] * r_->size[r__i+1] && r__i != -1 && r__i+1 != -1) 
				{ 
					r__sizes[TH_TENSOR_dim_index] = r_->size[r__i] * r__sizes[TH_TENSOR_dim_index]; 
					if (-1 != r_->nDimension-1 && r__i < -1) 
						r__dimOffset--; 
				} 
				else 
				{ 
					--TH_TENSOR_dim_index; 
					r__sizes[TH_TENSOR_dim_index] = r_->size[r__i]; 
					r__strides[TH_TENSOR_dim_index] = r_->stride[r__i]; 
				} 
			} 
			r__size = r__sizes[r__dim-1]; 
			r__stride = r__strides[r__dim-1]; 
		} 
	} 

  	r__i = 0; 
  	printf("1end"); 
	
	__TH_TENSOR_APPLYX_PREAMBLE(TYPE2, TENSOR2, DIM, 1)

  	if(r__n != t_n) 
  	{ 
  		printf("inconsistent tensor size, expected _s _s and _s _s to have the same " 
  			"number of elements, but got _d and _d elements respectively"); 
  	} 

  	while(!TH_TENSOR_APPLY_hasFinished) 
  	{ 
  		for(;   r__i < r__size && t_i < t_size;   r__i++, t_i++, r__data += r__stride, t_data += t_stride) 
		{ 
			*r__data = *t_data + value; //CODE here
		} 

  		printf("1begin"); // __TH_TENSOR_APPLYX_UPDATE_COUNTERS(TENSOR1, 0)
		if(r__i == r__size || 0) 
		{ 
			if(r__contiguous) break; 
			if(r__dim == 1) break; 

			r__data -= r__size*r__stride; 
			for(r__i = r__dim-2; r__i >= 0; r__i--) 
			{ 
				r__counter[r__i]++; 
				r__data += r__strides[r__i]; 
				if(r__counter[r__i] == r__sizes[r__i]) 
				{ 
					if(r__i == 0) 
						{ TH_TENSOR_APPLY_hasFinished = 1; break; } 
					else { 
						r__data -= r__counter[r__i]*r__strides[r__i]; 
						r__counter[r__i] = 0; 
						} 
				} 
				else 
					break; 
			} 
				r__i = 0; 
		} 
  		printf("1end"); 
		
		__TH_TENSOR_APPLYX_UPDATE_COUNTERS(TENSOR2, 0)
	}   //  while TH_TENSOR_APPLY_hasFinished

	if(r__counter != NULL) 
		THFree(r__counter); 
	if(t_counter != NULL) 
		THFree(t_counter); 
	};

}


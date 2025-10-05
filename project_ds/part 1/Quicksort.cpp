int Partition(vector<float> &v, vector<string> &v0, int s, int e){

	int p = e;
	int j = s;
	for(int i=s;i<e;++i){
		if(v[i]<v[p]){
			swap(v[i],v[j]);
			swap(v0[i],v0[j]);
			++j;
		}
	}
	swap(v[j],v[p]);
	swap(v0[j],v0[p]);
	return j;

}


void Quicksort(vector<float> &v, vector<string> &v0, int s, int e ){

	if(s<e){
		int p = Partition(v,v0,s,e);
		Quicksort(v,v0,s,p-1);
		Quicksort(v,v0,p+1,e);
	}

}

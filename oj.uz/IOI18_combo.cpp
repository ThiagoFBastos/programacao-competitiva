#include "combo.h"
 
std::string guess_sequence(int N) {
  std :: string S, ch = "ABXY";
  
  if(press("AB")) S += press("A") ? "A" : "B";
  else S += press("X") ? "X" : "Y"; 
 
  if(N == 1) return S;
 
  for(int i = 0; i < 4; ++i) {
	 if(ch[i] == S[0]) {
		ch.erase(ch.begin() + i);
		break;
	 }
  }
	
  for(int k = 2; k < N; ++k) {
	 std :: string A = S + ch[0] + ch[0];	
	 std :: string B = S + ch[0] + ch[1];
	 std :: string C = S + ch[0] + ch[2];
	 std :: string D = S + ch[1];
	 A += B;
	 A += C;
	 A += D;
	 int p = press(A);
	 if(p < k) S += ch[2];
	 else if(p == k) S += ch[1];
	 else S += ch[0];
  }
 
  std :: string P = S + ch[0] + S + ch[1];
 
  if(press(P) < N) S += ch[2];
  else if(press(S + ch[0]) == N) S += ch[0];
  else S += ch[1];
 
  return S;  
}

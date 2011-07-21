#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <queue>
#include <sstream>
#include <string>
#define ffor(_a,_f,_t) for(int _a=(_f),__t=(_t);_a<__t;_a++)
#define all(_v) (_v).begin() , (_v).end()
#define sz size()
#define pb push_back
#define SET(__set, val) memset(__set, val, sizeof(__set))
#define FOR(__i, __n) ffor (__i, 0, __n)
#define syso system("pause")
 
using namespace std;
char str[100010];
int n, len[100000], tmp;
bool eq[100000];
 
/*
  Naive approach, just for checking.
*/
int naive(){
  int ret = 0, len;
  FOR (i, n){
    len = 1;
    ffor (a, 1, n + 1){
      if (i - a < 0 || i + a > n - 1)
        break;
      if (str[i - a] != str[i + a])
        break;
      len += 2;
    }
    ret >?= len;
  }
  
  FOR (i, n){
    len = 0;
    ffor (a, 1, n + 1){
      if (i - a  + 1 < 0 || i + a > n - 1)
        break;
      if (str[i - a + 1] != str[i + a])
        break;
      len += 2;
    }
    ret >?= len;
  }
 
  return ret;
}
 
int longestPalindrom(){
  int ret = 0, id1, id2, a;
  
  // do it first for odd-length palindroms
  FOR (i, n){
    len[i] = 1;
    eq[i] = 0;
  }
  
  // fix each character as center
  FOR (i, n){
    
    // if we already expanded around this center as much as 
    // possible, just skip this character
    if (eq[i])
      continue;
      
    // len[i] holds length of palindrome for which we are 
    // sure that exists, so don't check it again, just continue
    id1 = i - (len[i] + 1) / 2;
    id2 = i + (len[i] + 1) / 2;
    while (id1 > -1 && id2 < n && str[id1] == str[id2]){
      id1--;
      id2++;
    }
    
    id1++;
    id2--;
    
    // now update lengths array for each character of right
    // part of ust found palindrome
    for (int j = i - 1; j >= id1; j--){
      a = i - j;
      
      // if for some center we know that it can't be 
      // expanded further, we can just skip it, 
      // because there is no sense to update it any more
      if (eq[i + a])
        continue;
        
      // if current center we are updating is not suffix
      // (or its opposite character is not prefix) of
      // found palindrome, then we should mark that center
      // as impossible for further expanding. We are doing that
      // by setting eq[i + a] = true
      // Else, if it is suffix (or its opposite character is
      // prefix) then we should update length
      tmp = j - len[j] / 2;
      if (tmp > id1){
        eq[i + a] = true;
        len[i + a] = len[j];
      }
      else if (tmp == id1){
        len[i + a] >?= len[j];
        break;
      }
      else{
        len[i + a] >?= ((j - id1) << 1) + 1;
        break;
      }
    }
    
    ret >?= len[i] = id2 - id1 + 1;
    if (id2 == n - 1)
      break;
  }
// 20
// acaacacacacccccaccac
 
  // then do it for even-length palindroms
  FOR (i, n)
    len[i] = eq[i] = 0;
  
  FOR (i, n){
    if (eq[i])
      continue;
      
    id1 = i - len[i] / 2;
    id2 = i + len[i] / 2 + 1;
    while (id1 > -1 && id2 < n && str[id1] == str[id2]){
      id1--;
      id2++;
    }
    
    id1++;
    id2--;
    for (int j = i - 1; j >= id1; j--){
      a = i - j;
      if (eq[i + a])
        continue;
 
 
      tmp = j - len[j] / 2 + 1;
      if (tmp > id1){
        eq[i + a] = true;
        len[i + a] = len[j];
      }
      else if (tmp == id1){
        len[i + a] >?= len[j];
        break;
      }
      else{
        len[i + a] >?= ((j - id1) << 1);
        break;
      }
    }
    
    ret >?= len[i] = id2 - id1 + 1;
    if (id2 == n - 1)
      break;
  }
 
  return ret;
}
 
int main(){
  scanf("%d", &n);
  scanf("\n%s", str);
/*  srand((unsigned)time(0));
  n = rand() % 1000 + 1;
  SET(str, 0);
  FOR (i, n)
    str[i] = 'a' + rand() % 2;*/
    
//  printf("%s\n", str);
  printf("%d\n", longestPalindrom());
/*  printf("%d\n", naive());
  syso;*/
  return 0;
}

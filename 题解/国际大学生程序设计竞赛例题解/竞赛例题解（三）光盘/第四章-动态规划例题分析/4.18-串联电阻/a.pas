{$A+,B-,D+,E+,F-,G-,I+,L+,N-,O-,P-,Q-,R+,S+,T-,V+,X+,Y+}
{$M 65520,0,655360}
type waynum=string[29];     {���ַ�����ʽ��Ŵ�����}
var 
f1,f2:text;   {�ļ�����}
    ways:array[0..1999] of waynum;   {ways[i]��ʾ�õ���ֵΪi�ĵ���ķ�����}
    v:array[1..20] of integer;         {v���ÿ�е������ֵ}
    rmake:array[1..1999] of integer;   {rmake�����Ҫ�������ֵ}
    b,n,t,nmax,temp,i,j:integer;
    h,m,s,ms:word;
test1,test2:waynum;

procedure add(var a:waynum;b:waynum); {�߾��ȼӷ�}
var 
l,l1,l2,code,temp,i,j:integer;
    ia,ib:longint;
begin
l1:=length(a);    {��a��b��λ��}
l2:=length(b);
if (l1<=9) and (l2<=9) then {���a��b����longint�ı�ʾ��Χ��ֱ�Ӽ���}
begin
val(a,ia,code);   {��aת��Ϊlongint����ŵ�ia}
val(b,ib,code);   {��bת��Ϊlongint����ŵ�ib}
ia:=ia+ib;
str(ia,a);        {��iaת��Ϊ�ַ���a}
end
else begin
if l1>=l2 then {a��λ����С��b��λ�������b����a��}
begin
a:='0'+a;  {a����ǰ��0�������λ}
inc(l1);
j:=l1;
for i:=l2 downto 1 do {��β����ʼ��λ���}
begin
temp:=(ord(a[j])+ord(b[i])-96);
a[j-1]:=chr(ord(a[j-1])+temp div 10);   {��λ}
a[j]:=chr(temp mod 10+48);          {�����jλ������}
j:=j-1;
end;
for i:=l1-l2 downto 2 do {�������λ��λ������}
begin
if a[i]>'9' then   {����9����Ҫ��λ}
begin
a[i-1]:=chr(ord(a[i-1])+1);   {��λ}
a[i]:=chr(ord(a[i])-10);      {��λ����һ������}
end 
else break;
end;
if a[1]='0' then delete(a,1,1);    {��ǰ��0ɾ��}
end
else begin {a��λ��С��b��λ�������a����b�ϣ������������������}
b:='0'+b;
inc(l2);
j:=l2;
for i:=l1 downto 1 do{��β����ʼ��λ���}
begin
temp:=(ord(a[i])+ord(b[j])-96);
b[j-1]:=chr(ord(b[j-1])+temp div 10);  {��λ}
b[j]:=chr(temp mod 10+48);
j:=j-1;
end;
for i:=l2-l1 downto 2 do{�������λ��λ������}
begin
if b[i]>'9' then 
begin 
b[i-1]:=chr(ord(b[i-1])+1);  {��λ}
b[i]:=chr(ord(b[i])-10);   {��λ����һ������}
end else break;
end;
if b[1]='0' then delete(b,1,1);
a:=b;   {���ѽ�����浽a}
end;
end;
end;

begin
assign(f1,'Resist.in');  reset(f1);    {ָ����������ļ�}
assign(f2,'Resist.out');  rewrite(f2);
readln(f1,b); {���������b}
while (b<>0) do
begin
for i:=1 to b do read(f1,v[i]); {����ÿ�е������ֵ}
readln(f1);
readln(f1,n); 
nmax:=n;      {nmax�������Ҫ�������ֵ}
t:=0;           {t����Ҫ�������ֵ����}
while (n<>0) do  {��������Ҫ����ĸ���ֵn}
begin
inc(t);
rmake[t]:=n;   {����Ҫ�������ֵ���浽rmake��}
if n>nmax then nmax:=n;
readln(f1,n);
end;
for i:=0 to nmax do ways[i]:='1'; {��ʼ��ÿ����ֵ�Ļ��;����Ϊ1}
for i:=2 to b do {����������״̬ת�Ʒ������}
for j:=v[i] to nmax do add(ways[j],ways[j-v[i]]); 
for i:=1 to t do writeln(f2,ways[rmake[i]]); {������}
readln(f1,b); {���������b}
  	end;
close(f1); {�ر��ļ�}
close(f2); {�ر��ļ�}
end.

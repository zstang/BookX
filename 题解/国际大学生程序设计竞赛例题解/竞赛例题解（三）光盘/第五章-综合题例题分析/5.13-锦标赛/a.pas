program Tournament_Seeding;
var
seed: array[0..127] of Integer;
  {seed[Index] = ��������λ��ΪIndex��ѡ�ֵ���������}
place: array[1..128] of Integer;
  {place[Index] = ���ӱ��Index��ѡ���ھ������е�λ��}
i, j, k, r, n, m, place1, place2, cur, min: Integer;
  {����nλѡ�ֲμӵĽ������У�ʵ��Ϊm�ľ��������ڵ�min�ֳ���}
begin
  {Ԥ������������128�˵ľ�����}
seed[0]:= 1; {��֪����}
r := 64; k := 2; {r=2i-1Ϊ��i�����б������������ѡ�ֵ�λ�þ��룻k=28-i}
for i := 7 downto 1 do
begin
	j := 0; {����֪���������Ƶ�����λ�õ����ӱ��}
	while j < 128 do
	begin
seed[j + r]:= k + 1 - seed[j]; {��i�����б��������ʵ������28-i+1}
j := j + 2 * r;
	end;
	r := r div 2; k := k * 2;
end;
{�����������ķ�����õ���һ���ӱ�ŵ�ѡ���ھ������е�λ�ñ�}
for i := 0 to 127 do place[seed[i]]:= i;
Read(n, m); {��������}

r := 0; k := n - 1; {�ܹ���r=?log2n?�־���}
while k > 0 do
begin
k := k div 2; r:=r+1;
end;

min := 8; {��ʼ��min}
for i := 1 to (m - 1) div 2 do {ö���������ӱ��i��m-i}
if (i <= n) and (m - i <= n) then {����λѡ���ڵڼ��־���������}
	begin
cur := 0; {�ӵ�һ�ֿ�ʼ�ж�}
	  place1 := place[i]; {ȡ����λѡ���ھ������е�λ��}
	  place2 := place[m - i];
	  repeat
        cur:=cur+1;
	    place1 := place1 div 2; {�ߵ�������λ�ã��൱ѡ�ֽ���}
		place2 := place2 div 2;
	  until place1 = place2; {��λ����ͬ�����ڵ�cur������}
	  cur := cur - (7 - r);
  if (cur < min) then min := cur; {��cur��min���磬�����min}
	end;
Writeln(min); {������}
end.

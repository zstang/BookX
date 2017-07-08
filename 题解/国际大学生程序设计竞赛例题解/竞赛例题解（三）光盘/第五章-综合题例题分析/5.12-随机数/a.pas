Program Random_Numbers;
const
  Digits = 30; {����������󳤶�}
  O = 10000; {������Ȩֵ}
  MaxN = 200;    {N���ֵΪ200}
  MaxM = 200;    {M���ֵΪ200}

type
  Long = record {�Զ��峤��������}
           D: Integer; {���������ȣ���log10OλΪ��λ��}
           Num: array[0..Digits] of Word; {�洢��������ÿλȨΪO��}
         end;

function Max(a, b: Integer): Integer;   {����a��b���ߵ����ֵ}
begin
   if a < b then Max := b else Max := a
end;

{ �Զ��峤�������� } 
procedure SetInt(var a: Long; x: Integer); {���ó�����a��ֵΪx��x<O��}
begin
   a.D := 0; a.Num[0] := x;   {x<=65535��ֱ�ӱ��浽���λ����}
end;

procedure Add(var x, y, res: Long); {�������ӷ���res=x+y}
var
  carry: Word; {��λ��־}
  i: Integer;
begin
  carry := 0; i := 0;  {��λ��־carry����}
  repeat
    if i <= x.D then carry:=carry+x.Num[i];   {��Ӧλ���}
    if i <= y.D then carry:=carry+y.Num[i];
    res.Num[i] := carry mod O;   {�����iλ����}
    carry := carry div O;        {�����λ}
    i:=i+1;      {�������λ}
  until (carry = 0) and (i > x.D) and (i > y.D);   {�ӵ͵��ߣ���λ���}
  res.D := i - 1;    {������λ��}
end;


procedure Sub(var x, y, res: Long); {�������ӷ���res=x-y��x��y��}
var
  carry: Word; {��λ��־}
  i: Integer;
begin
  carry := 1; i := 0;   {��λ��־carry��1}
  repeat
    if i <= x.D then carry:=carry+x.Num[i];              {��Ӧλ���}
    if i <= y.D then carry:=carry+(O - 1 - y.Num[i])
                else carry:=carry+(O - 1);
    res.Num[i] := carry mod O;
    carry := carry div O;        {��λ}
    i:=i+1;        {�������λ}
  until (carry = 1) and (i > x.D) and (i > y.D);   {�ӵ͵��ߣ���λ���}
  i:=i-1;
  while (i > 0) and (res.Num[i] = 0) do i:=i-1; {������ǰ��������}
  res.D := i;      {������λ��}
end;

procedure Div2(var a, res: Long); {��������2��res=a div 2}
var
  i: Integer;
  carry: Word; 
begin
  carry := 0;   {��λ��2������}
  for i := a.D downto 0 do   {�Ӹߵ��ͣ���λ����}
  begin
    carry := carry * O + a.Num[i];
    res.Num[i] := carry div 2;   {����}
    carry := carry mod 2        {���㵱ǰ����}
  end;
  i := a.D;
  while (i > 0) and (res.Num[i] = 0) do i:=i-1; {������ǰ��������}
  res.D := i;     {������λ��}
end;
function Cmp(var x, y: Long): Integer;             { 1 ��x>y}
var                          {�������ȽϺ�����Cmp =  0 ��x=y}
i: Integer;                                     { -1 ��x<y}
begin
  if x.D > y.D then Cmp := 1 {��x�ĳ��ȱ�y����x>y}
  else if x.D < y.D then Cmp := -1 {��x�ĳ��ȱ�y����x<y}
  else begin {�����ֵ���Ƚ�}
         for i := x.D downto 0 do {�Ӹ�λ����λ����һ�Ƚ�}
           if x.Num[i] > y.Num[i] then begin Cmp := 1; exit end
           else if x.Num[i] < y.Num[i] then begin Cmp := -1; exit end;
         Cmp := 0;  {���ֶ���ͬ�������������}
  end;
end;

var
  Bellman: array[1..MaxM] of Long; {�洢Bellman����}
  M, N: Integer;
  Long1, A, B, T, Number, Sum: Long; {Number=G(1,T,0.b1b2��bp)}
  cur, i, j: Integer;
  c: char;

begin
Assign(Input, 'random.in'); Reset(Input);    {ָ����������ļ�}
  Assign(Output, 'random.out'); Rewrite(Output);
  Readln(M, N);

  SetInt(Long1, 1); {���ó���1}

  for j := N to M do SetInt(Bellman[j], 1); {˳��Bellman����}
  for i := N - 1 downto 1 do
  begin
    SetInt(Bellman[i], 0);
    for j := M - 1 downto i do {Bellman[M]�����1}
      Add(Bellman[j], Bellman[j + 1], Bellman[j]);
         {�������ʽ��Bellman[i-1,j] := Bellman[i,j] + Bellman[i,j+1]}
  end;
  SetInt(T, 0); 
  for j := 1 to M do Add(T, Bellman[j], T); {ͨ��Bellman�������T}

  SetInt(A, 1); {����G(1,T,0.b1b2��bp)}
  SetInt(B, 0); Add(B, T, B); {A=1,B=T}
  repeat Read(c); until c = '.'; Read(c); {����С����}
  while ((c = '0') or (c = '1')) and (Cmp(A, B) <> 0) do {ģ����ַ�}
  begin   {c�ǵ�ǰ��С��λ}
if c = '0' then begin Add(A, B, B); Div2(B, B) end
                      {�õ����� (A, (A+B) div 2) }
               else begin Add(A, B, A); Div2(A, A); Add(A, Long1, A) end;
                          {�õ����� ((A+B) div 2+1, B) }
    Read(c)
  end;
  SetInt(Number, 0); Add(Number, A, Number); {Number=G(1,T,0.b1b2��bp)}
                                             {Number���������±�}
  {������Number��Ӧ��u����}
  cur := 1;
  for i := 1 to N do
  begin
    SetInt(Sum, 0); {�ۼӺͳ�ʼ��}
    cur:=cur-1;
    while Cmp(Number, Sum) = 1 do {���iλ������}
    begin
      cur:=cur+1;
      Add(Sum, Bellman[cur], Sum) {�ۼ�Bellman����}
	end;
	if i > 1 then Write(' '); {���u���еĵ�iλ����cur}
	Write(cur);
	Sub(Sum, Bellman[cur], Sum); {����һ�����ֵ�λ��}
	Sub(Number, Sum, Number);
	{����Bellman���飬�ָ�����һ�׶ε�Bellman����}
	for j := i to M - 1 do Sub(Bellman[j], Bellman[j + 1], Bellman[j]);
end;

Writeln;
  Close(Input); Close(Output); {�ر��ļ�}
end.

program copy_books;  const ifn='books.dat';	 {�����ļ���}       ofn='books.out';	{����ļ���}       maxsize=500;		{��������}

type datatype=array[1..maxsize] of longint;

var dt:array[1..maxsize] of ^datatype;	
{��¼j��������i���˵ĸ�������ҳ��}				 way:array[1..maxsize] of ^datatype;
{��¼j��������i���ˣ���i���˷��䵽����ı���} sum:array[1..maxsize] of ^datatype;
{��¼�ӵ�i��������j�����ҳ���ܺ�} book:array[1..maxsize] of longint;
{��¼��i�����ҳ��}     m,k:longint;  function max(x,y:longint):longint;	{���������еĴ���} begin   if x>y then max:=x          else max:=y; end;  procedure read_data;		{��������} var f:text;     i,j:longint; begin   assign(f,ifn);     {ָ�������ļ�}   reset(f);
    readln(f,m,k);
    for i:=1 to k do begin    {�����ڴ�ռ�}
      new(dt[i]);
      new(way[i]);
    end;
    for i:=1 to m do read(f,book[i]);      {����ÿ�����ҳ��}
    for i:=1 to m do begin     {����ҳ���ܺ�sum[i][j]}
      new(sum[i]);
      sum[i]^[i]:=book[i];
      for j:=i+1 to m do sum[i]^[j]:=sum[i]^[j-1]+book[j]; 
    end;
  close(f); {�ر��ļ�}
end;

procedure solve;	{���ƹ���}
var i,j,l,x:longint;
begin
	{��ʼ������}   dt[1]^[1]:=book[m];               {���鶼��������һ����}   for i:=2 to m do dt[1]^[i]:=dt[1]^[i-1]+book[m-i+1];
	{����}		   for i:=2 to k do               {��i����}    for j:=i to m do begin          {����ǰj����}      dt[i]^[j]:=maxlongint;      for l:=i-1 to j-1 do begin        {��i-1�����ܹ�����l����}        x:=sum[m-j+1]^[m-l];                {���㵹����i���˷����ҳ��}
       if max(x,dt[i-1]^[l])<=dt[i]^[j] then  {�õ�һ���õķ��䷽��}
        begin
          dt[i]^[j]:=max(x,dt[i-1]^[l]);
          way[i]^[j]:=l;            {��¼�´�ʱ��ʼһ���˷����˶��ٱ���}
        end;
     end;
   end;
end;

procedure write_data;	{������}
var f:text;
    i,a,b:longint;
begin
  assign(f,ofn);  {ָ������ļ�}
  rewrite(f);
    a:=1;  b:=m;        {a����ʼ��ţ�b��ʣ�µ�������}
    for i:=k downto 2 do begin   {���ÿһ���˵ķ��䷽��}
      writeln(f,a,' ',m-way[i]^[b]);  {��i���˷������ʼ�����ֹ��}
      a:=m-way[i]^[b]+1;
      b:=way[i]^[b];
    end;
    writeln(f,a,' ',m);    {���һ���˷���ʣ�µ���}
  close(f); {�ر��ļ�}
end;

begin		{������}
  read_data;    {��������}
  solve;        {��̬�滮���}
  write_data;   {������}
end.

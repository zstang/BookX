var
  f1,f2:text;
  n,max:integer;
  a:array[1..2,1..100,1..200]of boolean;  {a���ÿһ�������ǵĺû����}

procedure main;		{������}
var
  i,j,h,l,k:integer;   {i,k������ö�������ε�����}
begin
  h:=0;   {h�Ǳ�ǣ����ҵ�ȫ�������ξ���h=1}
  for i:=1 to n-1  do           {����n=2ʱ���ǳ��ϵ�������}
    for j:=1 to (n+1-i-1) do
      begin
        k:=2*j-1;
        a[2,i,k]:=(a[1,i,k])and(a[1,i,k+2])and(a[1,i,k+1])and(a[1,i+1,k]);
                  {�жϰ������ĸ����������Ƿ���ȫ�׵�}
        if a[2,i,k] then h:=1;
      end;
  for i:=1 to n-1 do            {����n=2ʱ���ǳ��µ�������}
    for j:=2 to (n-i-1) do
      begin
        k:=2*j;
        a[2,i,k]:=(a[1,i+1,k])and(a[1,i+1,k-1])and(a[1,i,k-2])and(a[1,i,k]);
                  {�жϰ������ĸ����������Ƿ���ȫ�׵�}
        if a[2,i,k] then h:=1;
      end;
  l:=2;
  while h<>0 do   {ѭ��Ѱ�Ҹ����������}
    begin
      inc(max); inc(l);       {max�ǵ�ǰ�׶������εĴ�С}
      h:=0;                   {h����Ƿ��б߳�Ϊmax�ĺ�������}
      a[1]:=a[2];             {�����н����ŵ�a[1]��׼����һ�׶ε���}
      for i:=1 to n-l+1 do
        begin
          for j:=1 to (n+1-i-l+1) do    {���㶥�ǳ��ϵ�������}
            begin
              k:=2*j-1;
              a[2,i,k]:=(a[1,i,k])and(a[1,i,k+2])and(a[1,i+1,k]);
                  {�ж�B,C,D�������Ƿ���ȫ�׵�}
              if a[2,i,k] then h:=1;
            end;
          for j:=l to (n+1-i-l)do       {���㶥�ǳ��µ�������}
            begin
              k:=2*j;
              a[2,i,k]:=(a[1,i,k])and(a[1,i+1,k-2])and(a[1,i+1,k]);
                  {�ж�B,C,D�������Ƿ���ȫ�׵�}
              if a[2,i,k] then h:=1;
            end;
        end;
    end;
  writeln(f2,max*max);   {�����������ε����}
end;

procedure init;	{�����ʼ��}
var
  ch:char;
  i,j,k:integer;
  s:string;
begin
  assign(f1,'triangle.dat'); reset(f1);   {ָ����������ļ�}
  assign(f2,'triangle.out'); rewrite(f2);
  readln(f1,n);    {���������δ�Сn}
  while n<>0 do
    begin
      max:=0; j:=n;
      for i:=1 to n do        {���������ε�ÿһ��}
        begin
          readln(f1,s); k:=0;
          while s[1]=' ' do delete(s,1,1);  {ɾ��ÿһ��ǰ��Ŀո�}
          while k<2*(n+1-i)-1 do
            begin
              inc(k);
              if s[1]='#' then a[1,i,k]:=false else
                if s[1]='-' then begin a[1,i,k]:=true; max:=1; end;
                               {����ÿ��С�����εĺû��������Ϊ��ʼ����}
              delete(s,1,1);
            end;
        end;
       main;             {���}
       readln(f1,n);     {׼��������һ��������}
     end;
  close(f1); close(f2); {�ر��ļ�}
end;

begin   {������}
  init;   {�����ʼ��}
end.

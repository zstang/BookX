program Dominoes;

const ifn='domino.dat';		{���������ļ���}
      ofn='domino.out';		{������ļ���}
      maxn=1000;            {���Ƶ��������}
      maxdot=6;             {����������}

type gaptype=array[-maxdot*maxn..maxdot*maxn] of integer;

var domino:array[1..maxn] of integer;
        {domino��¼ÿ����Ƶ��������Ĳ�ֵ}
    gap,addgap,g:^gaptype;
    n:integer;

procedure read_data;	{��������}
var i,a,b:integer;
begin
  assign(input,ifn);  {ָ�������ļ�}
  reset(input);
    readln(n);        {�����������}
    for i:=1 to n do begin
      readln(a,b);
      domino[i]:=a-b;  {ֻ�����������Ĳ���㹻�ˣ�����ʲô����û�й�ϵ}
    end;
  close(input); {�ر��ļ�}
end;

procedure solve;	{���ö�̬�滮˼��Ѱ�����Ž�}
var min,max:integer;
    i,j,k:integer;
begin
  new(gap);  new(addgap);   {�����ڴ�ռ�}
  for i:=-maxdot*maxn to maxdot*maxn do begin   {��ʼ��}
    gap^[i]:=maxn;
    addgap^[i]:=maxn;
  end;
  gap^[0]:=0;    {��ʼ����û�й��ƣ�����Ҫ��ת�Ϳ����������²��ֵΪ0}
  min:=0;  max:=0;
  for i:=1 to n do begin   {��������һ�������}
    for j:=min to max do
      if gap^[j]<maxn then begin
        k:=j+domino[i];     {��i����Ʋ���}
        if gap^[j]<addgap^[k] then addgap^[k]:=gap^[j];
        k:=j-domino[i];     {��i����Ʒ�תһ��}
        if gap^[j]+1<addgap^[k] then addgap^[k]:=gap^[j]+1;
        gap^[j]:=maxn;
      end;
    min:=min-abs(domino[i]);   {������ܴﵽ����С���������²��ֵ}
    max:=max+abs(domino[i]);
    g:=gap;                    {�����������飬׼��������һ�����}
    gap:=addgap;
    addgap:=g;
  end;
end;

procedure write_data;	{�����}
var min,k:integer;
begin
  assign(output,ofn);   {ָ������ļ�}
  rewrite(output);
    min:=maxn;  k:=-1;
    repeat                  {Ѱ����С�Ĳ�ֵ}
      inc(k);
      if gap^[k]<min then min:=gap^[k];
      if gap^[-k]<min then min:=gap^[-k];
    until min<maxn;
    writeln(min);           {�����ֵ}
  close(output); {�ر��ļ�}
end;

begin		{������}
  read_data;    {��������}
  solve;        {��̬�滮����}
  write_data;   {������}
end.

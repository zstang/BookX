type str=string;
const max=10000;          {��ʾ�����}
var input,output:text;
n,fk,i,len:byte;      {n���������Ŀ��fk�Ǳ����Ĺ�ģ}
                      {len���ı�����}
    map:array[0..255] of integer;
    form:array[1..200] of record        {form��������}
                             s:str;       {s���ַ���}
                             l:byte;      {l��s�ı���}
                          end;
    temp,doc:str;


  procedure init;	{�����ʼ������������}
  begin
    assign(input,'compress.dat');   {ָ����������ļ�}
    assign(output,'compress.out');
    reset(input);
    rewrite(output);
  end;

  function min(a,b:integer):integer;	{���������е�С��}
  begin
    if a<b then min:=a else min:=b;
  end;

  procedure workout;   {���ı�����ѹ��}
  var i,j:byte;
  begin
    for i:=1 to len do map[i]:=max; {��ʼ���費��ѹ������Ϊ�����}
    map[0]:=0;
    j:=0;                 {jָʾ��ǰѹ�����е�λ��}
    while length(doc)>0 do
    begin
      for i:=1 to fk do   {�ڵ�ǰλ�ó���ʹ��ÿһ�ֱ���}
      if pos(form[i].s,doc)=1 then
         map[j+length(form[i].s)]:=
               min(map[j+length(form[i].s)],map[j]+form[i].l);

      delete(doc,1,1);    {λ��ǰ��һλ}
      inc(j);        
    end;
  end;

begin		{������}
  init;    {���������ʼ��}
  readln(input,n);
  readln(input,temp);     {�����ı�}
  for i:=1 to n do        
  begin
    fk:=0;           {fk�Ǳ����Ĺ�ģ}
    doc:=temp;
      readln(input,temp);
      while (temp[1]='(') and (temp<>'')   {��������}
      do
        begin
          inc(fk);
          form[fk].s:=copy(temp,2,pos(',',temp)-2);    {�����ַ���}
          form[fk].l:=length(temp)-pos(',',temp)-1;    {�������ĳ���}
          readln(input,temp);   {�����������һ��}
        end;
    len:=length(doc);    {���ı�����}
    workout;             {ѹ���ı�}
    if map[len]=max then writeln(output,0)   {���0��ʾ����ѹ���ı�}
    else writeln(output,map[len]);   {������}
  end;
  close(output); {�ر��ļ�}
  close(input); {�ر��ļ�}
end.

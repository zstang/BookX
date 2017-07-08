{$N+}
program Sum;

type P=record	{����ʽ����}
         l:integer;
         x:extended;
         p:array [0..30] of extended;
       end;

var fin,fout:text;
    n:integer;
    c:array [1..30,0..30] of extended; {��¼���������ֵ}
    e:array [0..30] of p;	{Sk(n)��ֵ}


procedure makeC;		{���������C(n,m)}
  var i,j:integer;
  begin
    fillchar(c,sizeof(c),0);
    c[1,0]:=1;c[1,1]:=1;
    for i:=2 to 22 do
      begin
        c[i,0]:=1;
        c[i,i]:=1;
        for j:=1 to i-1 do c[i,j]:=c[i-1,j-1]+c[i-1,j];
      end;
  end;


function nzc(a,b:extended):boolean;{�ж�b�Ƿ�������a}
  var temp:extended;
  begin
    nzc:=false;
    temp:=int(a/b);  {a����b����ȡ��}
    if abs(a-temp*b)<1e-5 then exit;
    if abs(a-(temp+1)*b)<1e-5 then exit;
    if abs(a-(temp-1)*b)<1e-5 then exit;
    nzc:=true;       {b��������a}
  end;


procedure reduce(var a:P);	{Լ��}
  var i,j:integer;
      flag:boolean;
  begin
    for i:=21 downto 2 do
      begin
        if nzc(a.x,i) then     {�ж�i�ܷ�������ĸ}
continue;
        flag:=false;
        for j:=0 to a.l do
        if nzc(a.p[j],i) then  {�ж�i�ܷ��������з���}
          begin
            flag:=true;
            break;
          end;

        if flag then       {flag=true��ʾi���Ƿ��Ӻͷ�ĸ�Ĺ�Լ��}
continue;
        for j:=0 to a.l do   {����������Լ��i}
        a.p[j]:=a.p[j]/i;
        a.x:=a.x/i;
      end;
  end;


procedure add(a,b:P;var c:p);	{����ʽ���}
  var i,j,l:integer;
  begin
    fillchar(c,sizeof(c),0);
    if a.l>b.l then c.l:=a.l else c.l:=b.l;   {ȡ���ϵ��}
    c.x:=a.x*b.x;                             {ͨ��}
    for i:=0 to a.l do a.p[i]:=a.p[i]*b.x;    
    for i:=0 to b.l do b.p[i]:=b.p[i]*a.x;
    for i:=0 to c.l do c.p[i]:=a.p[i]+b.p[i];  {�������}
    reduce(c);                                {Լ��}
  end;


procedure main; {������}
  var i,j,k:integer;
      temp:p;
      sn:string;

  begin
    assign(fin,'sum.dat');   {ָ�������ļ�����������}
    reset(fin);
    readln(fin,n);
    close(fin); {�ر��ļ�}

fillchar(e,sizeof(e),0);
{�߽�������k=1}
    with e[0] do
      begin
        x:=1;
        l:=1;
        p[1]:=1;p[0]:=0;
      end;

{������Sk(n)��ֵ}
    for k:=2 to n+1 do
      begin
        with e[k-1] do
          begin
            l:=k;
            x:=1;
            p[l]:=1;
          end;
       
 for i:=2 to k do  {���õ��ƹ�ʽ���}
          begin
            temp:=e[k-i];
            with temp do
              begin
                if i mod 2=0 then
                  for j:=0 to l do p[j]:=p[j]*c[k,i]
                else
                 for j:=0 to l do p[j]:=-p[j]*c[k,i];
              end;
            add(e[k-1],temp,e[k-1]);
          end;
        e[k-1].x:=e[k-1].x*k;
        reduce(e[k-1]);  {���Լ�֣����e[k-1]�����ʽ}
      end;
	
{������}
    assign(fout,'sum.out'); {ָ������ļ�}
    rewrite(fout);
    write(fout,e[n].x:0:0);   {�����ĸ}
    with e[n] do
    for i:=l downto 0 do write(fout,' ',p[i]:0:0); {�����ϵ������}
    close(fout); {�ر��ļ�}
  end;

begin  {������}
  makeC;   {���������}
  main;    {����Sk(n)}
end.

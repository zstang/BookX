{$M 65520,0,655360}
{$r-,i-,n+}
program package;
type
  lightnode=array[1..4] of integer;  {��ʾ״̬����Ҫ���ֵ��ݵĸ���}

  packagetype=record       {��ʾ��ѡ����װ������}
    la:integer;          {���}
    va:real;             {�۸�}
    nu:lightnode;        {����ʽ}
  end;

  node=array[0..999] of real;    {����״̬�Ŀռ�}

const   {��������ļ�}
  inputname='package.in';
  outputname='package.out';

var
  pa:array[1..50] of packagetype;{�������п�ѡ����װ������}
  ne:array[1..50] of integer;    {��������ʱ���湺�򷽰�} 
  r:lightnode;                   {�˿͵Ĺ�������}
  w:array[1..4] of longint;      {����ĳһ״̬�������е�λ��ʱ�õĲ���}
  min:array[0..999] of ^node;    {��������״̬����С����}
  n:byte;                        {��ѡ����װ����}
  temp:lightnode;
  i,j:integer;

  procedure readdata;   {��������}
  var
    f:text;
    s,s1:string;
    i,j,k:integer;
  begin
    assign(f,inputname);  {ָ�������ļ�}
    reset(f);

    readln(f,n);
    for i:=1 to n do              {����ÿ���Ż���װ}
    begin
      read(f,pa[i].la,pa[i].va);   {�����źͼ۸�}
      readln(f,s);                 {���빺��ʽ}
      s:=s+' ';
      for j:=1 to 4 do
        if pos(chr(96+j),s)>0 then   {Ѱ�ҵ������ͣ�abcd}
        begin
          k:=pos(chr(96+j),s)+2;      {Ѱ�Ҷ�Ӧ����}
          s1:='';                        {�ѱ�ʾ�������ַ���ת��Ϊ����}
          while s[k]<>' ' do begin s1:=s1+s[k]; inc(k); end;
          val(s1,pa[i].nu[j],k);
        end
        else pa[i].nu[j]:=0;          {���û�и����͵ĵ������ʾ����Ҫ����}
    end;

    readln(f,s);                   {����˿�Ҫ��ĵ����ͺź�����}
    s:=s+' ';
    for j:=1 to 4 do      {Ѱ�ҵ������ͣ�abcd}
      if pos(chr(96+j),s)>0 then
      begin
        k:=pos(chr(96+j),s)+2;
        s1:='';                {�ѱ�ʾ�������ַ���ת��Ϊ����}
        while s[k]<>' ' do begin s1:=s1+s[k]; inc(k); end;
        val(s1,r[j],k);
      end
      else r[j]:=0;

    close(f); {�ر��ļ�}
  end;

  procedure getready; {��ʼ��}
  var
    i,j:integer;
    tot:longint;
    temp:packagetype;
  begin
for i:=1 to n-1 do   {����װ����Ŵ�С��������}
      for j:=i+1 to n do if pa[i].la>pa[j].la then
      begin
        temp:=pa[i];
        pa[i]:=pa[j];
        pa[j]:=temp;
      end;

    tot:=1;         {ͳ������tot�Լ�����洢��λ������w}
    for i:=1 to 4 do
    begin
      w[i]:=tot;
      tot:=tot*(1+r[i]);
    end;

    {���洢��һ����״̬����ֵ���������ռ䣬������ֵ}
    tot:=tot div 1000;
    for i:=0 to tot do 
    begin
      new(min[i]);
      fillchar(min[i]^,sizeof(min[i]^),0);
    end;
    min[0]^[0]:=1;
  end;

  procedure change(s:lightnode; var la1,la2:integer);
  {����ĳһ״̬�������е�λ��}
  var
    tot:longint;
    i:byte;
  begin
    tot:=0;
    for i:=1 to 4 do tot:=tot+w[i]*s[i];
    la1:=tot div 1000;
    la2:=tot-la1*1000;
  end;

  procedure getmin(s:lightnode; la1,la2:integer);
  {�������״̬Ϊsʱ������ֵ}
  var
    i,j:byte;
    nla1,nla2:integer;
  begin
    min[la1]^[la2]:=1e30;

    for i:=1 to n do  {����ʹ��ÿһ���Ż���װ}
      if ((s[1]>0) and (pa[i].nu[1]>0)) or ((s[2]>0) and (pa[i].nu[2]>0)) or
         ((s[3]>0) and (pa[i].nu[3]>0)) or ((s[4]>0) and (pa[i].nu[4]>0)) then
      {Ҫ״̬�б仯�Ų���}
      begin
        for j:=1 to 4 do
        begin
          temp[j]:=s[j]-pa[i].nu[j];
          if temp[j]<0 then temp[j]:=0; 
          {��ΪֻҪ����˿�Ҫ�󼴿ɣ����Թ������ɶ���������}
        end;
        change(temp,nla1,nla2); {����洢λ��n1a1,n1a2}

        if min[nla1]^[nla2]=0 then getmin(temp,nla1,nla2);
                  {����ʹ���˵�i���Ż���װ֮��ʣ�µĻ���Ҫ���ٻ���}
                  {�����ǰ���������������Ҫ�ٴ��ظ�}

        if min[la1]^[la2]>min[nla1]^[nla2]+pa[i].va then
          min[la1]^[la2]:=min[nla1]^[nla2]+pa[i].va;
      end;
  end;

  procedure getsolve(s:lightnode; la1,la2:integer);
  {����С���õĹ��򷽰�}
  var
    i,j:byte;
    nla1,nla2:integer;
  begin
    for i:=1 to n do   {����ʹ��ÿһ���Ż���װ}
    begin
      for j:=1 to 4 do
      begin
        temp[j]:=s[j]-pa[i].nu[j];
        if temp[j]<0 then temp[j]:=0;
      end;
      change(temp,nla1,nla2); {����洢λ��n1a1,n1a2}

      if abs(min[la1]^[la2]-min[nla1]^[nla2]-pa[i].va)<0.001 then
                       {�ж�ʹ�ø��Ż��ܷ�ﵽ���������ֵ}
      begin
        inc(ne[i]);
        getsolve(temp,nla1,nla2);
        break;
      end;
    end;
  end;

  procedure print(re:lightnode;la1,la2:integer);  {������}
  var
    f:text;
    i:byte;
  begin
    fillchar(ne,sizeof(ne),0);
    getsolve(re,la1,la2);   {����С���õĹ��򷽰�}

    assign(f,outputname);  {ָ������ļ�}
    rewrite(f);
    writeln(f,min[la1]^[la2]-1:0:2);    {�������}
    for i:=1 to n do if ne[i]>0 then     {�������}
    begin
      write(f,pa[i].la);
      if ne[i]>1 then write(f,'(',ne[i],') ')
      else write(f,' ');
    end;
    close(f); {�ر��ļ�}
  end;

begin   {������}
  readdata;    {��������}
  getready;    {��ʼ��}
  change(r,i,j);   {����״̬r��λ��}
  getmin(r,i,j);   {����״̬r������ֵ}
  print(r,i,j);   {������}
end.

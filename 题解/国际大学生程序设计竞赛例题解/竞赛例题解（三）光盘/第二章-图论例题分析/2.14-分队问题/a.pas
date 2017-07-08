program division;
const
  ifn='division.in';
  ofn='division.out';

const
  maxn=1000;

var
  know:array[1..maxn,1..3] of integer;
     {know���ڽӱ���¼ÿ������ʶ������Щ��}
  du,now:array[1..maxn] of integer;
     {du��¼ÿ������ʶ��������Ҳ����ͼ�ж���Ķȣ�}
     {now��¼��ǰ�ֶӷ�����ÿ������ʶ��ͬ���˵�����}
  n,m:longint;
     {n������}
  ans:array[1..maxn] of boolean;
     {ans��¼�ֶ������ans[i]=true��ʾi�ڵ�һ��}

procedure read_data;   {��������}
var
  i,x,y:longint;
begin
  assign(input,ifn);   {ָ�������ļ�}
  reset(input);

    fillchar(know,sizeof(know),0);  {know��du�������㣬��ʼ���ڽӱ�}
    fillchar(du,sizeof(du),0);
    readln(n,m);
    for i:=1 to m do begin         {����ѡ��֮����ʶ�����������ͼ���ڽӱ�}
      readln(x,y);
      inc(du[x]);  know[x,du[x]]:=y;
      inc(du[y]);  know[y,du[y]]:=x;
    end;

  close(input);    {����������ر��ļ�}
end;

procedure mend_du1(x:longint);
                {����x����֮��ԭ����xͬ�ӵ�����ͼ�ж���ȵ����}
var
  i:longint;
begin
  {���know[x,i]��x����ʶ��ͬ�ӣ���ô���Ӻ�Ͳ���ͬ����ʶ��}
  for i:=1 to du[x] do 
    if ans[know[x,i]]=ans[x] then dec(now[know[x,i]]);
end;

function mend_du2(x:longint):longint; 
                {����x����֮��ԭ����x��ͬ�ӵ�����ͼ�ж���ȵ����}
var
  i,y:longint;
begin
  y:=0;
  for i:=1 to du[x] do          {Ѱ��x������һ�Ӻ�������ʶ��ͬ�ӵ���y}
    if ans[know[x,i]]=ans[x] then begin
      y:=know[x,i];
      break;
    end;
  if y>0 then inc(now[y]);   {�޸�����˵���ʶ����������ʶ��x��}
  now[x]:=du[x]-now[x];      {x��Ϊ���ӣ���ʶ�Ͳ���ʶ���˸պ��෴}
  mend_du2:=y;     {���������ʶ���ˣ����û���򷵻�0}
end;

procedure change(x:longint); {��������}
var
  y:longint;
begin
  repeat
    mend_du1(x);          {ԭ����xͬ�ӵ�����ͼ�ж���ȵ����}
    ans[x]:=not ans[x];   {x������һ��}
    y:=mend_du2(x);       {ԭ����x��ͬ�ӵ�����ͼ�ж���ȵ����}
    if y=0 then break;         {��Ϊx���ӿ��ܵ���yͬ����ʶ��������}
    if now[y]<=1 then break;   {���y����Ҫ�������˳�}
    x:=y;                      {���򣬼���ѭ��������y}
  until false;
end;

procedure divi;  {�ֶ�}
var
  i:longint;
begin
  {һ��ʼ���������˶��ڵ�һ�ӣ��ڶ���û����}
  fillchar(ans,sizeof(ans),true); 
  now:=du;
  {�����ֶ����}
  for i:=1 to n do  {����������ͬ������ʶ����һ���ˣ��ͽ��е���}
    if now[i]>1 then change(i);
end;

procedure write_data;    {������}
var
  i,k:longint;
begin
  assign(output,ofn);    {ָ������ļ�}
  rewrite(output);

    k:=0;                {ͳ�Ƶ�һ������k}
    for i:=1 to n do
      if ans[i] then inc(k);
    write(k);
    for i:=1 to n do      {��ӡ��һ�ӳ�Ա}
      if ans[i] then write(' ',i);
    writeln;
    write(n-k);          {������˶���ڶ���}
    for i:=1 to n do
      if not ans[i] then write(' ',i);

  close(output);        {�����ϣ��ر�����ļ�}
end;

begin     {������}
  read_data;    {��������}
  divi;       {�ֶ�}
  write_data;   {������}
end.

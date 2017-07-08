{$A+,B-,D+,E+,F-,G-,I+,L+,N-,O-,P-,Q+,R+,S+,T-,V-,X+,Y+}
{$M 65520,0,655360}
program TinyBasicInterpreter;

const
     ipf='tbasic.dat';	{�����ļ���}
     opf='tbasic.out';	{����ļ���}
     max=100;

type
    TExpression=record  {���ʽ����}
                      etype:integer; {���ʽ����}(* 1 ... 3 *)
                      constant:integer; {�õ��ĳ���}
                      var1,var2:char;   {�õ��ı���}
    end;

    TStatement=record   {�������}
                     stype:integer;  {�������}(* 1 ... 5 *)
                     var1:char;        {�õ��ı���}
                     expr:TExpression; {�õ��ı��ʽ}
    end;

var f:text;
    prog:array[1..max] of TStatement;  {prog�洢TBASIC����}
    n:integer;                           {n��¼�����ж��������}
    variable:array['A'..'Z'] of integer;  {variable�洢������ֵ}

function s2i(s:string):integer;	{ �ַ���ת�������� }
var i,code:integer;
begin
     val(s,i,code);  {val�������ַ���sת��������i��������뱣����code}
     s2i:=i;
end;

procedure convert2(s:string; var expr:TExpression);
                    {���ַ�����ʽ�ı��ʽs�洢����¼expr��}
begin
     if s[1]>'9' then begin
        if s[2]='+' then expr.etype:=2     {����2��<����>+<����>}
                    else expr.etype:=3;    {����3��<����>><����>}
        expr.var1:=s[1];
        expr.var2:=s[3];
     end else begin
         expr.etype:=1;                    {����1��<����>}
         expr.constant:=s2i(s);
     end;
end;

procedure convert(s:string; var sm:TStatement); 
                    {���ַ�����ʽ�����s�洢����¼sm��}
var s1:string;
begin
     while not (s[1] in ['A'..'Z']) do delete(s,1,1);  {ɾ���к�}
     s1:=copy(s,1,pos(' ',s)-1);
     delete(s,1,pos(' ',s));
     while s[1]=' ' do delete(s,1,1);                  {ɾ������ո�}
     if s1='LET' then begin                   {����1��LET���}
        sm.stype:=1;
        sm.var1:=s[1];       {����Ⱥ���ߵĸ�ֵ����}
        delete(s,1,2);
        convert2(s,sm.expr);  {����Ⱥ��ұߵı��ʽ}
     end;
     if s1='PRINT' then begin                 {����2��PRINT���}
        sm.stype:=2;
        sm.var1:=s[1];        {������Ҫ��ӡ�ı��ʽ}
     end;
     if s1='GOTO' then begin                  {����3��GOOT���}
        sm.stype:=3;
        convert2(s,sm.expr);   {������ת�ı��ʽ}
     end;
     if s1='IF' then begin                    {����4��IF���}
        sm.stype:=4;
        convert2(s,sm.expr);     {�����������ʽ}
     end;
     if s='STOP' then begin                   {����5��STOP���}
        sm.stype:=5;
     end;
end;

procedure initialize;	{�����ʼ��}
var s:string;
begin
     assign(f,ipf); reset(f);   {ָ�������ļ�}
     n:=0;
     while not eof(f) do begin    {���ж���ʹ洢BASIC����}
           readln(f,s);        {����}
           inc(n);
           convert(s,prog[n]); {�洢}
     end;
     close(f); {�ر��ļ�}
     fillchar(variable,sizeof(variable),0);   {�����ռ��ʼ��}
end;

function result(expr:TExpression):integer;    {������ʽ}
begin
     if expr.etype=1 then result:=expr.constant;   {<����>}
     if expr.etype=2 then result:=variable[expr.var1]+variable[expr.var2];
                                                         {<����>+<����>}
     if expr.etype=3 then begin   {<����> > <����>}
        if variable[expr.var1]>variable[expr.var2] then result:=1
                                                   else result:=0;
     end;
end;

procedure run;	{����������}
var no:integer;       {no�ǳ�������ָ��}
    tmp:TStatement;
    over:boolean;
begin
     no:=1;           {�ӵ�һ����俪ʼ}
     over:=false;
     assign(f,opf); rewrite(f);    {ָ������ļ�}
     while not over do begin         {�������û�н��������ִ����ȥ}
           tmp:=prog[no];               {ȡ����ǰ��䣬������ִ��}
           case tmp.stype of
       {����1��LET���}
                1: begin variable[tmp.var1]:=result(tmp.expr);
                         inc(no);
                   end;
       {����2��PRINT���}
                2: begin writeln(f,tmp.var1,'=',variable[tmp.var1]);
                         inc(no);
                   end;
       {����3��GOOT���}
                3: no:=result(tmp.expr);
       {����4��IF���}
                4: if result(tmp.expr)=0 then inc(no,2)
                                         else inc(no);
       {����5��STOP���}
                5: over:=true;
           end;
     end;
     close(f); {�ر��ļ�}
end;

begin	{������}
     initialize;   {��ʼ��}
     run;          {ģ���������}
end.

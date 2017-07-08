Program Identifying_Real_Constant;

var
	LastChar: Char; {һ���ַ��Ļ�����}
	Buffered: Boolean; {��������־}

function getchar: Char; {�����������ַ�}
begin
	if not Buffered then Read(LastChar);  {���������û���ַ������һ��}
	Buffered := False;
	GetChar := LastChar;             {ȡ�������ַ�}
end;

procedure ungetc(c: char); {���������ط��ַ�}
begin
	LastChar := c;
	Buffered := True;
end;

function ReadThrough(match: string): Integer;
var                  {�����������ַ�����match����ƥ�䣬����ƥ����ַ�����}
	c: Char;         {c�ǵ�ǰ���������ַ�}
	num: Integer;    {ƥ����ַ�����}
begin
	num := 0;
	while true do
	begin
		c := getchar; {�����������ַ�c}
		if Pos(c, match) = 0 then {ƥ�����}
		begin
			ungetc(c);   {cû��ƥ�䣬���·��뻺����}
			break;
		end;
		Inc(num); {ƥ��ɹ���ƥ���ַ�����һ}
	end;
	ReadThrough := num;
end;

function Valid: Boolean; {ʶ���������Ƿ񸡵㳣��}
var
	hasdec, hasexp: Boolean;  {hasdec��ʾ�Ƿ���С��, hasexp��ʾ�Ƿ���ָ��}
	n: Integer;
begin
	Valid := False; Buffered := False;
	hasdec := False; hasexp := False; {��־��ʼ��}

	ReadThrough(' '); {������������ǰ���ո�}
	if ReadThrough('-+') > 1 then Exit; {���������}
	if ReadThrough('0123456789') = 0 then Exit; {���㳣��ȱ�޷�������}
	n := ReadThrough('.');
	if n > 1 then Exit; {���С����}
	if n = 1 then {�ַ����д���С������}
	begin
		 hasdec := True;   {��С�����}
		 if ReadThrough('0123456789') = 0 then Exit; {С������ȱ�޷�������}
	end;
	n := ReadThrough('eE');
	if n > 1 then Exit; {���e��E}
	if n = 1 then {�ַ����д���ָ������}
	begin
		 hasexp := True; {��ָ�����}
		 if ReadThrough('+-') > 1 then Exit; {���������}
		 if ReadThrough('0123456789') = 0 then Exit; {ָ������ȱ�޷�������}
	end;
	ReadThrough(' '); {�����������ĺ����ո�}
	if Pos(getchar, #13#10) = 0 then Exit; {���������ǻس�}
	if (not hasexp) and (not hasdec) then Exit; {����С����������ָ������}

	Valid := True;   {û���ҵ����󣬳�����ʾ�Ϸ�}
end;

const
	 res: array[Boolean] of string[3] = ('NO', 'YES');
begin
	 writeln(res[Valid]); {����Valid������ֵ���YES��NO}
end.

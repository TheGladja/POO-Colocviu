#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

class Malware{
protected:
  int rating;
  string data, nume, metInf, IdVirus;
  vector <string> modif;

public:
  Malware();
  string setId(string x);
  ~Malware();
};

string Malware::setId(string x)
{
  this-> IdVirus = x;
  return IdVirus;
}

Malware::Malware()
{
  rating = 0;
  data = "";
  nume = "";
  metInf = "unknown";
  modif = {};
  IdVirus = "";
}

Malware::~Malware()
{
  rating = 0;
  data = "";
  nume = "";
  metInf = "unknown";
  modif = {};
  IdVirus = "";
}

class Rootkit: virtual public Malware{
protected:
  vector <string> import;
  vector <string> comenzi;

public:
  Rootkit();
  ~Rootkit();

  friend istream& operator >> (istream& in, Rootkit& R);
  friend ostream& operator << (ostream& out, const Rootkit& R);
};

ostream& operator << (ostream& out, const Rootkit& R)
{
  out<<"\nRating-ul virusului este: "<<R.rating;
  out<<"\nData de infectare este: "<<R.data;
  out<<"\nNumele virusului este: "<<R.nume;
  out<<"\nMetoda de infectare este: "<<R.metInf;
  out<<"\nRegistrii modificati sunt: ";
  for(auto ir=R.modif.begin(); ir!=R.modif.end(); ir++)
    out<<(*ir)<<" ";
  out<<"\nStringurile comenzilor sunt: ";
  for(auto ir=R.comenzi.begin(); ir!=R.comenzi.end(); ir++)
    out<<(*ir)<<" ";
  out<<"\nStringurile importurilor sunt: ";
  for(auto ir=R.import.begin(); ir!=R.import.end(); ir++)
    out<<(*ir)<<" ";
  return out;
}

istream& operator >> (istream& in, Rootkit& R)
{
  string x = "1";
  cout<<"\nData de infectare(zi,luna,an): ";
  in>>R.data;
  cout<<"\nNumele virusului: ";
  in>>R.nume;
  cout<<"\nMetoda de infectare: ";
  in>>R.metInf;
  cout<<"\nRegistri modificati: ";
  while(x != "0")
  {
    in>>x;
    if(x=="HKLM-run" || x=="HKCU-run")
      R.rating += 20;
    if(x != "0")
      R.modif.push_back(x);
  }
  x = "1";
  cout<<"\nIntroduceti stringurile comenzilor(apasati tasta 0 pentru a termina): ";
  while(x != "0")
  {
      in>>x;
      if(x=="System Service Descriptor Table" || x=="SSDT" || x=="NtCreateFile")
        R.rating += 100;
      if(x != "0")
        R.comenzi.push_back(x);
  }
  cout<<"\nIntoduceti stringurile importurilor(apasati tasta 0 pentru a termina): ";
  x = "1";
  while(x != "0")
  {
    in>>x;
    if(x=="“ntoskrnl.exe")
      R.rating = R.rating * 2;
    if(x != "0")
      R.import.push_back(x);
  }
  return in;
}

Rootkit::Rootkit()
{
  Malware();
  import = {};
  comenzi = {};
}

Rootkit::~Rootkit()
{
  import = {};
  comenzi = {};
}

class Keylogger: virtual public Malware{
protected:
  vector <string> funct;
  vector <string> taste;

public:
  Keylogger();
  ~Keylogger();

  friend istream& operator >> (istream& in, Keylogger& K);
  friend ostream& operator << (ostream& out, const Keylogger& K);
};

ostream& operator << (ostream& out, const Keylogger& K)
{
  out<<"\nRating-ul virusului este: "<<K.rating;
  out<<"\nData de infectare este: "<<K.data;
  out<<"\nNumele virusului este: "<<K.nume;
  out<<"\nMetoda de infectare este: "<<K.metInf;
  out<<"\nRegistrii modificati sunt: ";
  for(auto ir=K.modif.begin(); ir!=K.modif.end(); ir++)
    out<<(*ir)<<" ";
  out<<"\nTastele modificate sunt: ";
  for(auto ir=K.taste.begin(); ir!=K.taste.end(); ir++)
    out<<(*ir)<<" ";
  out<<"\nFunctiile virusului sunt: ";
  for(auto ir=K.funct.begin(); ir!=K.funct.end(); ir++)
    out<<(*ir)<<" ";
  return out;
}

istream& operator >> (istream& in, Keylogger& K)
{
  string x = "1";
   cout<<"\nData de infectare(zi,luna,an): ";
  in>>K.data;
  cout<<"\nNumele virusului: ";
  in>>K.nume;
  cout<<"\nMetoda de infectare: ";
  in>>K.metInf;
  cout<<"\nRegistri modificati: ";
  while(x != "0")
  {
    in>>x;
    if(x=="HKLM-run" || x=="HKCU-run")
      K.rating += 20;
    if(x != "0")
      K.modif.push_back(x);
  }
  x = "1";
  cout<<"\nIntroduceti tastele(apasati tasta 0 pentru a termina): ";
  while(x != "0")
    {
      in>>x;
      if(x=="[Up]" || x=="[Num Lock]" || x=="[Down]" || x=="[Right]" || x=="[UP]" || x=="[Left]" || x=="[PageDown]")
        K.rating += 10; 
      if(x != "0")
        K.taste.push_back(x);
    }
  cout<<"\nIntroduceti functiile(apasati tasta 0 pentru a termina): ";
  x = "1";
  while(x != "0")
  {
    in>>x;
    if(x=="“CreateFileW" || x=="OpenProcess" || x=="ReadFile" || x=="WriteFile" || x=="RegisterHotKey" || x=="SetWindowsHookEx")
      K.rating += 30;
    if(x != "0")
      K.funct.push_back(x);
  }
  return in;
}

Keylogger::Keylogger()
{
  Malware();
  funct = {};
  taste = {};
}

Keylogger::~Keylogger()
{
  funct = {};
  taste = {};
}

class KernelKeylogger: public Rootkit, public Keylogger{
  bool ascunde;

public: 
  KernelKeylogger();
  ~KernelKeylogger();

  friend istream& operator >> (istream& in, KernelKeylogger& KK);
  friend ostream& operator << (ostream& out, const KernelKeylogger& KK);
};

ostream& operator<<(ostream& out, const KernelKeylogger& KK)
{
  out<<"\nRating-ul virusului este: "<<KK.rating;
  out<<"\nData de infectare este: "<<KK.data;
  out<<"\nNumele virusului este: "<<KK.nume;
  out<<"\nMetoda de infectare este: "<<KK.metInf;
  out<<"\nRegistrii modificati sunt: ";
  for(auto ir=KK.modif.begin(); ir!=KK.modif.end(); ir++)
    out<<(*ir)<<" ";
  out<<"\nStringurile comenzilor sunt: ";
  for(auto ir=KK.comenzi.begin(); ir!=KK.comenzi.end(); ir++)
    out<<(*ir)<<" ";
  out<<"\nStringurile importurilor sunt: ";
  for(auto ir=KK.import.begin(); ir!=KK.import.end(); ir++)
    out<<(*ir)<<" ";
  out<<"\nTastele modificate sunt: ";
  for(auto ir=KK.taste.begin(); ir!=KK.taste.end(); ir++)
    out<<(*ir)<<" ";
  out<<"\nFunctiile virusului sunt: ";
  for(auto ir=KK.funct.begin(); ir!=KK.funct.end(); ir++)
    out<<(*ir)<<" ";
  if(KK.ascunde==1)
    out<<"\nAcest virus ascunde fisiere";
  else out<<"\nAcest virus ascunde registri";
  return out;
}

istream& operator >> (istream& in, KernelKeylogger& KK)
{
  string x = "1";
   cout<<"\nData de infectare(zi,luna,an): ";
  in>>KK.data;
  cout<<"\nNumele virusului: ";
  in>>KK.nume;
  cout<<"\nMetoda de infectare: ";
  in>>KK.metInf;
  cout<<"\nRegistri modificati: ";
  while(x != "0")
  {
    in>>x;
    if(x=="HKLM-run" || x=="HKCU-run")
      KK.rating += 20;
    if(x != "0")
      KK.modif.push_back(x);
  }
  x = "1";
  cout<<"\nIntroduceti stringurile comenzilor(apasati tasta 0 pentru a termina): ";
  while(x != "0")
  {
      in>>x;
      if(x=="System Service Descriptor Table" || x=="SSDT" || x=="NtCreateFile")
        KK.rating += 100;
      if(x != "0")
        KK.comenzi.push_back(x);
  }
  cout<<"\nIntoduceti stringurile importurilor(apasati tasta 0 pentru a termina): ";
  x = "1";
  while(x != "0")
  {
    in>>x;
    if(x=="“ntoskrnl.exe")
      KK.rating = KK.rating * 2;
    if(x != "0")
      KK.import.push_back(x);
  }
  x = "1";
  cout<<"\nIntroduceti tastele(apasati tasta 0 pentru a termina): ";
  while(x != "0")
    {
      in>>x;
      if(x=="[Up]" || x=="[Num Lock]" || x=="[Down]" || x=="[Right]" || x=="[UP]" || x=="[Left]" || x=="[PageDown]")
        KK.rating += 10; 
      if(x != "0")
        KK.taste.push_back(x);
    }
  cout<<"\nIntroduceti functiile(apasati tasta 0 pentru a termina): ";
  x = "1";
  while(x != "0")
  {
    in>>x;
    if(x=="“CreateFileW" || x=="OpenProcess" || x=="ReadFile" || x=="WriteFile" || x=="RegisterHotKey" || x=="SetWindowsHookEx")
      KK.rating += 30;
    if(x != "0")
      KK.funct.push_back(x);
  }
  cout<<"\nAcest virus ascunde 1 - fisiere/0 - registri: ";
  in>>KK.ascunde;
  if(KK.ascunde == 1)
    KK.rating += 20;
  else KK.rating += 30; 
  return in;
}

KernelKeylogger::KernelKeylogger()
{
  Rootkit();
  Keylogger();
  ascunde = 0;
}

KernelKeylogger::~KernelKeylogger()
{
  ascunde = 0;
}


class Ransomware: public Malware{
  int criptare;
  double obfuscare;

public:
  Ransomware();
  ~Ransomware();

  friend istream& operator >> (istream& in, Ransomware& R);
  friend ostream& operator << (ostream& out, const Ransomware& R);
};

ostream& operator << (ostream& out, const Ransomware& R)
{
  out<<"\nRating-ul virusului este: "<<R.rating;
  out<<"\nData de infectare este: "<<R.data;
  out<<"\nNumele virusului este: "<<R.nume;
  out<<"\nMetoda de infectare este: "<<R.metInf;
  out<<"\nRegistrii modificati sunt: ";
  for(auto ir=R.modif.begin(); ir!=R.modif.end(); ir++)
    out<<(*ir)<<" ";
  out<<"\nRatingul de criptare este: "<<R.criptare;
  out<<"\nRatingul de obfuscare este: "<<R.obfuscare;
  return out;
}

istream& operator >> (istream& in, Ransomware& R)
{
  string x;
  cout<<"\nData de infectare(zi,luna,an): ";
  in>>R.data;
  cout<<"\nNumele virusului: ";
  in>>R.nume;
  cout<<"\nMetoda de infectare: ";
  in>>R.metInf;
  cout<<"\nRegistri modificati: ";
  while(x != "0")
  {
    in>>x;
    if(x=="HKLM-run" || x=="HKCU-run")
      R.rating += 20;
    if(x != "0")
      R.modif.push_back(x);
  }
  cout<<"\nRatingul de criptare: ";
  in>>R.criptare;
  cout<<"\nRatingul de obfuscare: ";
  in>>R.obfuscare;
  R.rating = R.criptare + R.obfuscare;
  return in;
}

Ransomware::Ransomware()
{
  Malware();
  criptare = 0;
  obfuscare = 0;
}

Ransomware::~Ransomware()
{
  criptare = 0;
  obfuscare = 0;
}

int main()
{
  unordered_map <int, vector<Malware>> M;
  int n, m, i, j;
  static int nrOrd;
  string x = "Calculatorul-", virus;
  cout<<"\nIntroduceti numarul de calculatoare: ";
  cin>>n;
  for(i=0; i<n; i++)
  {
    nrOrd = i+1;
    x = x + to_string(nrOrd);
    cout<<"\nIntroduceti numarul de virusi pe care il are calculatorul numarul "<<i+1<<" : ";
    cin>>m;
    for(j=0; j<m; j++)
        {
          cout<<"\nTipul de virus (Rootkit, Keylogger, KernelKeylogger, Ransomware): ";
          cin>>virus;
          if(virus=="Rootkit")
          {
            Rootkit r;
            cin>>r;
            M[nrOrd].push_back(r);
          }
           else if(virus=="Keylogger")
          {
            Keylogger r;
            cin>>r;
            M[nrOrd].push_back(r);
          }
          else if(virus=="KernelKeyLogger")
          {
            KernelKeylogger r;
            cin>>r;
            M[nrOrd].push_back(r);
          }
          else
          {
            Ransomware r;
            cin>>r;
            M[nrOrd].push_back(r);
          }
        }
  }
  return 0;
}
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#define h return
#define F printf
#define S struct
typedef float d;typedef int i;d H=1003;d w(){h drand48();}S v{d x,y,z;v(d a=0,d b=0,d
c=0){x=a;y=b;z=c;}v a(v b){h v(x+b.x,y+b.y,z+b.z);}v c(v b){h v(x*b.x,y*b.y,z*b.z);}d
e(v b){h x*b.x+y*b.y+z*b.z;}v f(d b){h v(x*b,y*b,z*b);}v n(d s=1){h f(s/sqrt(x*x+y*y+
z*z));}v p(v a){h v(y*a.z-z*a.y,z*a.x-x*a.z,x*a.y-y*a.x);}};S r{v o,a;r(v j,v k){o=j;
a=k;}v p(d t){h a.f(t).a(o);}};S s{v p;d l;i C(r q,d&t){v o=q.o.f(-1).a(p);d b=q.a.e(
o);d c=o.e(o)-l;c=b*b-c;if(c<0)h 0;c=sqrt(c);d v=b-c;if(v>0&&v<t){t=v;h 1;}h 0;}};i g
(d c){h pow(c<0?0:c>1?1:c,.45)*255+.5;}r C(d x,d y){v e=v(x,-y,1).n(4);d a=6*w(),c=.2
*sqrt(w());d b=sin(a)*c;a=cos(a)*c;e.x-=a;e.y-=b;h r(v(a,b),e.n());}s u[10] ={{v(0,-2
,5),1},{v(0,-H),1e6},{v(0,H),1e6},{v(H),1e6},{v(-H),1e6},{v(0,0,-H),1e6},{v(0,0,H+3),
1e6},{v(-2,-2,4),2},{v(2,-3,4),1},{v(2,-1,4),1}}; i p(r a,d&t){i n=-1;for(i m=0;m<10;
m++){if(u[m].C(a,t))n=m;}h n;}v e(r a,d b){d t=1e6;i o=p(a,t);if(b>5||o<0)h v();if(!o
)h v(.9,.5,.1);v P=a.p(t);v V=u[o].p.f(-1).a(P).n();if(o>7){a=r(P,a.a.a(V.f(-2*V.e(a.
a))));h e(a,++b).f((o-6.5)/2);}d O=6*w();d A=sqrt(w());v U=a.a.f(-1).p(V).n();v T=U.p
(V);a=r(P,T.f(cos(O)*A).a(U.f(sin(O)*A)).a(V.f(sqrt(1-A*A))).n());v j(1,1,1);if(o==3)
j.x=j.z=0;if(o==4)j.y=j.z=0;h e(a,++b).c(v(j));}i main(){F("P3\n512 512\n255\n");for(
i m=0;m<512;m++)for(i n=0;n<512;n++){v q;for(i k=0;k<100;k++){r j=C(n/256.0-1,m/256.0
-1);q=q.a(e(j,0).f(0.02));}F("%d %d %d ",g(q.x),g(q.y),g(q.z));}}
#include "mf.h"
#include <time.h>
#include <sys/stat.h>

double file_size2(char* filename)
{
    struct stat statbuf;
    stat(filename,&statbuf);
    double size=statbuf.st_size/1024.0;
 
    return size;
}

int test(int a,int b,int n,int d){
	//generate the parameters	
	mfp *par = malloc(sizeof(*par));
	
	mfp_new(par,d);
	
	printf("test a=%d,b=%d,m=%d,d=%d\n",a,b,n,d);

	double s1,s2,s3,s4,e1,e2,e3,e4,a1,a2,a3,a4,b1,b2,b3,b4;
	FILE *c1;
	FILE *c2;
	FILE *S1;
	FILE *S2;

	c1 = fopen("c1","wb");
	c2 = fopen("c2","wb");
	S1 = fopen("s1","wb");
	S2 = fopen("s2","wb");
	


	bn_t ***f = malloc(sizeof(bn_t**)*a);
	#pragma omp parallel for
	for(int k=0;k<a;k++)
	{
		f[k] = malloc(sizeof(bn_t*)*n);
		for(int i=0;i<n;i++)
		{
			f[k][i] = malloc(sizeof(bn_t)*d);
			for(int j=0;j<d;j++)
			{
				bn_new(f[k][i][j]);
				bn_rand_mod(f[k][i][j],par->p);
			}
		}
	}
//generate b * x(d*1)
	bn_t **x = malloc(sizeof(bn_t)*b);
	#pragma omp parallel for
	for(int k=0;k<b;k++)
	{
		x[k] = malloc(sizeof(bn_t)*d);
		for(int i=0;i<d;i++)
		{
			bn_new(x[k][i]);
			bn_rand_mod(x[k][i],par->p);
		}
	}
//test mmf	
	//printf("test a*b mf\n");
//keygen
//	mvkf *mvkf = malloc(sizeof(*mvkf));

	g1_t **W = malloc(sizeof(g1_t*)*a);
	mvkf **m_vkf = malloc(sizeof(mvkf)*a);
	#pragma omp parallel for
	for(int i=0;i<a;i++)
	{
		W[i] = malloc(sizeof(g1_t)*d);
		m_vkf[i] = malloc(sizeof(mvkf));
		mvkf_new(m_vkf[i],n);
		for(int j=0;j<d;j++)
		{
			g1_new(W[i][j]);
		}
	}

	s1 = omp_get_wtime();
	//#pragma omp parallel

	//#pragma omp for
	#pragma omp parallel for
	for(int i=0;i<a;i++)
	{
		//printf("i = %d, I am Thread %d\n", i, omp_get_thread_num());
		mmf_keygen(W[i],m_vkf[i],f[i],n,par);
	}
	e1 = omp_get_wtime();
	//printf("The keygen time was: %f\n", (double)(e1 - s1) );

//progen
	g1_t *vkx = malloc(sizeof(g1_t)*b);
	#pragma omp parallel for	
	for(int i=0;i<b;i++)
	{
		g1_new(vkx[i]);
	}
	s2 = omp_get_wtime();
	#pragma omp parallel for
	for(int i=0;i<b;i++)
	{
		//printf("i = %d, I am Thread %d\n", i, omp_get_thread_num());
		mf_prg(vkx[i],x[i],par);
	}
	e2 = omp_get_wtime();
	//printf("The progen time was: %f\n", (double)(e2 - s2) );
//compute 
	bn_t ***y = malloc(sizeof(bn_t**)*a);
	#pragma omp parallel for
	for(int k=0;k<a;k++)
	{
		y[k] = malloc(sizeof(bn_t*)*b);	
		
		for(int i=0;i<b;i++)
		{
			y[k][i] = malloc(sizeof(bn_t)*n);
			for(int j=0;j<n;j++)
			{
				bn_new(y[k][i][j]);
			}
		}
	
	}
	g1_t **V = malloc(sizeof(g1_t*)*a);
	#pragma omp parallel for
	for(int k=0;k<a;k++)
	{
		V[k] = malloc(sizeof(g1_t)*b);
		for(int j=0;j<b;j++)
		{
			g1_new(V[k][j]);
		}
	}

	s3 = omp_get_wtime();
	#pragma omp parallel for
	for(int k=0;k<a;k++)
	{
		//#pragma omp atomic		
		//printf("k = %d, I am Thread %d\n", k, omp_get_thread_num());
		for(int j=0;j<b;j++)
		{
			mmf_comp(y[k][j],V[k][j],W[k],f[k],x[j],n,par);
		}
	}
	e3 = omp_get_wtime();
	printf("The ts1 time was: %f\n", (double)(e3 - s3) );
	//printf("The compute time was: %f\n", (double)(e3 - s3));
//	fq_mat_print_pretty(Y,par->ctx);
//verify
	s4 = omp_get_wtime();
	//int flag = mmf_vrfy(mvkf,vkx,y,V,n,par);
	int flag = 0;
	#pragma omp parallel for
	for(int k=0;k<a;k++)
	{
		for(int j=0;j<b;j++)
		{
			flag = flag + mmf_vrfy(m_vkf[k],vkx[j],y[k][j],V[k][j],n,par);
		}
	}
	e4 = omp_get_wtime();
	//printf("The verify time was: %f\n", (double)(e4 - s4) );
	printf("The tc1 time was: %f\n", (double)(e1+e2+e4 - s4-s2-s1) );
	//printf("flag is:%d\n",flag);
printf("-------------------------------------\n");
//test mf
	//printf("test a*b*n*f\n");
//keygen
	g1_t ***W2 = malloc(sizeof(g1_t**)*a);
	vkf ***vkf2 = malloc(sizeof(vkf**)*a);
	#pragma omp parallel for
	for(int k=0;k<a;k++)
	{
		W2[k] = malloc(sizeof(g1_t*)*n);
		vkf2[k] = malloc(sizeof(vkf*)*n);
		for(int i=0;i<n;i++)
		{
			W2[k][i] = malloc(sizeof(g1_t)*d);
			vkf2[k][i] = malloc(sizeof(vkf));
			for(int j=0;j<d;j++)
			{
				g1_new(W2[k][i][j]);
			}
		}
	}
	a1 = omp_get_wtime();
	#pragma omp parallel for
	for(int k=0;k<a;k++)
	{
		for(int i=0;i<n;i++)
		{
			mf_keygen(W2[k][i],vkf2[k][i],f[k][i],par);
		}
	}
	b1 = omp_get_wtime();
	//printf("The keygen2 time was: %f\n", (double)(b1 - a1) );
	//printf("The progen2 time was: %f\n", (double)(e2 - s2) );
//compute
	
	bn_t ***y2 = malloc(sizeof(bn_t**)*a);
	g1_t ***V2 = malloc(sizeof(g1_t**)*a);
	#pragma omp parallel for
	for(int k=0;k<a;k++)
	{
		y2[k] = malloc(sizeof(bn_t*)*b);
		V2[k] = malloc(sizeof(g1_t*)*b);
		for(int i=0;i<b;i++)
		{
			y2[k][i] = malloc(sizeof(bn_t)*n);
			V2[k][i] = malloc(sizeof(g1_t)*n);
			for(int j=0;j<n;j++)
			{
				bn_new(y2[k][i][j]);
				g1_new(V2[k][i][j]);
			}
		}
	
	}
	a3 = omp_get_wtime();
	#pragma omp parallel for
	for(int k=0;k<a;k++)
	{
		for(int i=0;i<b;i++)
		{
			for(int j=0;j<n;j++)
			{
				mf_comp(y2[k][i][j],V2[k][i][j],W2[k][j],f[k][j],x[i],par);
			}
		}
	
	}

	b3 = omp_get_wtime();
	printf("The ts2 time was: %f\n", (double)(b3 - a3) );
//verify
	int flag2 = 0;
	a4 = omp_get_wtime();
	#pragma omp parallel for
	for(int k=0;k<a;k++)
	{
		for(int i=0;i<b;i++)
		{
			
			for(int j=0;j<n;j++)
			{
				flag2 = flag2 + mf_vrfy(vkf2[k][j],vkx[i],y2[k][i][j],V2[k][i][j],par);
			}
		}
	
	}
	b4 = omp_get_wtime();
	//printf("The verify2 time was: %f\n", (double)(b4 - a4) );
	printf("The tc2 time was: %f\n", (double)(b1+e2+b4 - a4-s2-a1) );
	//printf("flag is:%d\n",flag2);

	


//free
	mfp_free(par);
	free(par);
	#pragma omp parallel for
	for(int k=0;k<a;k++)
	{
		for(int i=0;i<n;i++)
		{
			for(int j=0;j<d;j++)
			{
				fwrite(&f[k][i][j],sizeof(bn_t),1,c1);
				fwrite(&f[k][i][j],sizeof(bn_t),1,c2);
				bn_free(f[k][i][j]);
			}
			free(f[k][i]);
		}
		free(f[k]);
	}
	free(f);
	#pragma omp parallel for
	for(int k=0;k<b;k++)
	{
		for(int i=0;i<d;i++)
		{
			fwrite (&x[k][i],sizeof(bn_t),1,c1);
			fwrite (&x[k][i],sizeof(bn_t),1,c2);
			bn_free(x[k][i]);
		}
		free(x[k]);
	}
	free(x);
	#pragma omp parallel for
	for(int i=0;i<a;i++)
	{
		for(int j=0;j<d;j++)
		{
			fwrite (&W[i][j],sizeof(g1_t),1,c1);
			g1_free(W[i][j]);
		}
		free(W[i]);
		//fwrite (&m_vkf[i]->a,sizeof(bn_t),1,S1);
		fwrite (&m_vkf[i]->k,sizeof(bn_t),1,S1);

		for(int k=0;k<n;k++)
		{
			fwrite (&m_vkf[i]->r[k],sizeof(bn_t),1,S1);
		}
		
		mvkf_free(m_vkf[i],n);
		free(m_vkf[i]);
	}
	free(m_vkf);
	free(W);
	#pragma omp parallel for
	for(int i=0;i<b;i++)
	{
		fwrite (&vkx[i],sizeof(g1_t),1,S1);
		fwrite (&vkx[i],sizeof(g1_t),1,S2);
		g1_free(vkx[i]);
	}
	free(vkx);
	#pragma omp parallel for
	for(int k=0;k<a;k++)
	{
		for(int i=0;i<b;i++)
		{
			for(int j=0;j<n;j++)
			{
				fwrite (&y[k][i][j],sizeof(bn_t),1,c1);
				bn_free(y[k][i][j]);
			}
			free(y[k][i]);
		}
		free(y[k]);
	}
	free(y);
	#pragma omp parallel for
	for(int k=0;k<a;k++)
	{
		for(int j=0;j<b;j++)
		{
			fwrite (&V[k][j],sizeof(g1_t),1,c1);
			g1_free(V[k][j]);
		}
		free(V[k]);
	}
	free(V);

	#pragma omp parallel for
	for(int k=0;k<a;k++)
	{
		for(int i=0;i<n;i++)
		{
			for(int j=0;j<d;j++)
			{
				fwrite (&W2[k][i][j],sizeof(g1_t),1,c2);
				g1_free(W2[k][i][j]);
			}
			fwrite (&vkf2[k][i],sizeof(vkf),1,S2);
			free(vkf2[k][i]);
			free(W2[k][i]);
		}
		free(vkf2[k]);
		free(W2[k]);
	}
	free(vkf2);
	free(W2);
	#pragma omp parallel for
	for(int k=0;k<a;k++)
	{
		for(int i=0;i<b;i++)
		{
			for(int j=0;j<n;j++)
			{
				fwrite (&y2[k][i][j],sizeof(bn_t),1,c2);
				fwrite (&V2[k][i][j],sizeof(g1_t),1,c2);
				bn_free(y2[k][i][j]);
				g1_free(V2[k][i][j]);
			}
			free(y2[k][i]);
			free(V2[k][i]);
		}
		free(y2[k]);
		free(V2[k]);
	}
	free(y2);
	free(V2);

	fclose (c1);
	fclose (c2);
	fclose (S1);
	fclose (S2);
	printf("communication size = %f\t%f\n",file_size2("c1")/1024.0,file_size2("c2")/1024.0);
	printf("storage size = %f\t%f\n",file_size2("s1"),file_size2("s2"));
	return 0;

}



int main(int argc, char **argv)
{
//initialize the projec
	sinit();

	/*int a = 100;
	int b = 10;
	int n = 10;
	int d = 10;*/
	test(50,50,50,50);
printf("*************************************\n");
	for(int i=100;i<=500;i+=50)
	{
	//a	
		test(i,50,50,50);
printf("*************************************\n");
	//b
		test(50,i,50,50);
printf("*************************************\n");
	//m
		test(50,50,i,50);
printf("*************************************\n");
	//d
		test(50,50,50,i);
printf("*************************************\n");
	}

	sclose();
	return 0;
}


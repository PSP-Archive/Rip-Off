//------------------------------------------------------------------------------

#include "MathCon.h"
#include "Matrix44f.h"
#define EPS 1E-2

//From gxbase, modified
//some methods are marked with //added to gxbase Matrix44f

/**************************************************************************\
 *
 * This file is part of the GXBase graphics library.
 * Copyright (C) 2003-2006 James Ward, Department of Computer Science,
 * University of Hull. All rights reserved.
 * 
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
 *
 \**************************************************************************/

//------------------------------------------------------------------------------


/**
 * Return inverse of a matrix (can throw)
 */

Matrix44f Matrix44f::Inverted() const
{
    // This is what gets thrown on an error
    const char *myError = "Cannot invert";

    int i,j,k;						// Loop indices

    float a[4][8];
    for (i=0;i<4;i++) {
      for (j=0;j<4;j++) {
         a[i][j]   = m[i][j];
         a[i][j+4] = (float)(i==j?1.0:0.0);
      }
    }

    int order[4];					// Pivot order
    int flags[4]={1,1,1,1};			// All rows available as pivot

    for (i=0;i<4;i++) {				// work along columns finding pivot
      float pivot = 0;				// max value in column
      int pivotIndex = 0;			// row containing pivot
      for (j=0;j<4;j++)
         if ((flags[j]) && (fabs(a[j][i]) > pivot)) {
            pivot = (float)fabs(a[j][i]);
            pivotIndex = j;
         }

#ifndef _SPSP
      if (!pivot) throw myError;    // Error
#endif

      pivot = a[pivotIndex][i];		// get it with sign

      flags[pivotIndex] = 0;
      order[i] = pivotIndex;

      for (k=i+1;k<8;k++)
         a[pivotIndex][k] /= pivot;	// normalize equation

      for (j=0;j<4;j++)
         if (j != pivotIndex) {
            float mult = a[j][i];	// row multiplier
            for (k=i+1;k<8;k++)
               a[j][k] -= mult * a[pivotIndex][k];
         }
    }

    // copy result: return
    Matrix44f m;
    for (i=0;i<4;i++) {
      int rowNumber = order[i];
      for (j=0;j<4;j++)
         m[i][j] = a[rowNumber][j+4];
    }

    return m;
}


//------------------------------------------------------------------------------


/**
 * Return transpose of matrix
 */

Matrix44f Matrix44f::Transposed() const
{
    Matrix44f R;
	R[0][1] = m[1][0]; R[0][2] = m[2][0]; R[0][3] = m[3][0]; R[0][0] = m[0][0];
	R[1][0] = m[0][1]; R[1][2] = m[2][1]; R[1][3] = m[3][1]; R[1][1] = m[1][1];
	R[2][0] = m[0][2]; R[2][1] = m[1][2]; R[2][3] = m[3][2]; R[2][2] = m[2][2];
	R[3][0] = m[0][3]; R[3][1] = m[1][3]; R[3][2] = m[2][3]; R[3][3] = m[3][3];
	return R;
}


//---- Translation -------------------------------------------------------------


/**
 * Make a translation matrix
 */

const Matrix44f &
Matrix44f::MakeTranslate ( const Vector3f &v )
{
    Identity();
    m[0][3] = v.x();
    m[1][3] = v.y();
    m[2][3] = v.z();
    return *this;
}


//---- Scaling -----------------------------------------------------------------


/**
 * Makes a scale matrix
 */

const Matrix44f &
Matrix44f::MakeScale ( const Vector3f &v )
{
    Identity();
    m[0][0] = v.x();
    m[1][1] = v.y();
    m[2][2] = v.z();
    return *this;
}


//---- MakeRotateX(a) ----------------------------------------------------------


/**
 * Rotation about X axis
 */

const Matrix44f & Matrix44f::MakeRotateX ( float a )
{
    float ar = (float)a;
    float CA = (float)cos(ar), SA = (float)sin(ar);

    m[0][0]=1.0; m[0][1]= 0.0; m[0][2]= 0.0; m[0][3]=0.0;
    m[1][0]=0.0; m[1][1]=  CA; m[1][2]= -SA; m[1][3]=0.0;
    m[2][0]=0.0; m[2][1]=  SA; m[2][2]=  CA; m[2][3]=0.0;
    m[3][0]=0.0; m[3][1]= 0.0; m[3][2]= 0.0; m[3][3]=1.0;

    return *this;
}


//---- MakeRotateY(a) ----------------------------------------------------------


/**
 * Rotation about Y axis
 */

const Matrix44f & Matrix44f::MakeRotateY ( float a )
{
   float ar = (float)a;
   float CA = (float)cos(ar), SA = (float)sin(ar);

   m[0][0]= CA; m[0][1]= 0.0; m[0][2]=  SA; m[0][3]=0.0;
   m[1][0]=0.0; m[1][1]= 1.0; m[1][2]= 0.0; m[1][3]=0.0;
   m[2][0]=-SA; m[2][1]= 0.0; m[2][2]=  CA; m[2][3]=0.0;
   m[3][0]=0.0; m[3][1]= 0.0; m[3][2]= 0.0; m[3][3]=1.0;

   return *this;
}


//---- MakeRotateZ(a) ----------------------------------------------------------


/**
 * Rotation about Z axis
 */

const Matrix44f & Matrix44f::MakeRotateZ ( float a )
{
   float ar = (float)a;
   float CA = (float)cos(ar), SA = (float)sin(ar);

   m[0][0]= CA; m[0][1]= -SA; m[0][2]= 0.0; m[0][3]=0.0;
   m[1][0]= SA; m[1][1]=  CA; m[1][2]= 0.0; m[1][3]=0.0;
   m[2][0]=0.0; m[2][1]= 0.0; m[2][2]= 1.0; m[2][3]=0.0;
   m[3][0]=0.0; m[3][1]= 0.0; m[3][2]= 0.0; m[3][3]=1.0;

   return *this;
}

const Matrix44f& Matrix44f::AlignOyToD(const Vector3f& d){
	float norm=d.Length();
	if (norm<EPS){
		Identity();							//check if d is an acceptable vector, must not happen
		return *this;
	}

	float r=sqrtf(d.z()*d.z()+d.y()*d.y());			
	if (r<EPS){								//r is for sure >=0, so is enough to test <EPS
		//int his case d is Ox (phi=+/-PI/2, theta =?)
		float angle=(float)PI/2.0f;
		if (d.x()>0){
			MakeRotateZ(angle);
			return *this;
		}else{
			//dx<0, it can't be 0 because the norm would have been 0
			MakeRotateZ(-angle);
			return *this;
		}
	}

	float phi=atanf(d.x()/sqrtf(r));
	//float phi=asinf(max(min(d.x/norm,1.0f),-1.0f));
	float theta=atan2f(d.z(),d.y());
	Matrix44f m1, m2; 
	
	MakeRotateX(theta);
	m2.MakeRotateZ(-phi);
	(*this) = m2* (*this);			//Rox(theta)*Roz(-phi)
	return *this;										
}




//added to gxbase Matrix44f
const Matrix44f & Matrix44f::AlignOxToD ( const Vector3f& d){
	float norm=d.Length();
	if (norm<EPS){
		Identity();		//check if d is an acceptable vector, must not happen
		return *this;
	}

	norm=1.0f/norm;
	float x,y,z;
	x=d.x()*norm;
	y=d.y()*norm;
	z=d.z()*norm;
	//if (d.x()<1+EPS && d.x()>1-EPS && d.y()<EPS && d.y()>-EPS && d.z()<EPS && d.z()>-EPS)
	//	return;
	float r=x*x+y*y;
	if (r<EPS){
		//int his case d is Oz (phi=+/-PI/2, theta =?)
		float angle=(float)PI/2.0f;
		if (z>0){
			MakeRotateY(angle);
			return *this;
		}else{
			//z<0, it can't be 0 because the norm would have been 0
			MakeRotateY(-angle);
			return *this;
		}
	}
	//float phi=asinf(max(min(z,1.0f),-1.0f));
	float phi=atanf(z/sqrtf(r));			//maybe faster than max/min above?!
	float theta;//=atan2f(y,x);
	if (y<EPS && y>-EPS){ 
		if (x>=0){
			theta=0.0f;
		}
		else {
			theta=180.0f*DegRad;
		}
	} else theta=atan2f(y,x);
	MakeRotateZ(theta);
	Matrix44f m; 
	m.MakeRotateY(-phi);
	(*this)=m*(*this);						//Roz(theta)*Roy(-phi)
	return *this;
}

const Matrix44f & Matrix44f::AlignOxToD2D ( const Vector3f& d){
	float norm=d.Length();
	if (norm<EPS){
		Identity();		//check if d is an acceptable vector, must not happen
		return *this;
	}

	norm=1.0f/norm;
	float x,y,z;
	x=d.x()*norm;
	y=d.y()*norm;
	z=d.z()*norm;

	float theta=0.0f;		//in radians
	if (y<EPS && y>EPS){
		if (x>=0.0f)
			theta=0.0f;
		else theta=PI;
	}else{
		if (x<EPS && x>EPS){
			if (y>0) theta=PI/2.0f;
			else theta=-PI/2.0f;
		}else{
			//if (y>=0) 
				theta=PI+atan(y/x);
			//else theta=-PI+atan(y/x);
		}
		
		//theta=atan2f(y,x);
		//if (x>0)
		//	theta=atan(y/x);
		//else 
	}
	MakeRotateZ(theta);
	return *this;
}

//added to gxbase Matrix44f
const Matrix44f & Matrix44f::AlignDToOx ( const Vector3f& d){
	float norm=d.Length();
	if (norm<EPS){
		Identity();		//check if d is an acceptable vector, must not happen
		return *this;
	}
	norm=1.0f/norm;
	float x,y,z;
	x=d.x()*norm;
	y=d.y()*norm;
	z=d.z()*norm;
	float r=x*x+y*y;
	if (r<EPS){
		//int his case d is Oz (phi=+/-PI/2, theta =?)
		float angle=(float)PI/2.0f;
		if (z>0){
			MakeRotateY(-angle);
			return *this;
		}else{
			//z<0, it can't be 0 because the norm would have been 0
			MakeRotateY(angle);
			return *this;
		}
	}
	//float phi=asinf(max(min(z,1.0f),-1.0f));				
	float phi=atanf(z/sqrtf(r));			//maybe faster than max/min above?!
	if (y*y+z*z<EPS){
		Identity();
		return *this;
	}
	
	float theta=atan2f(y,x);
	MakeRotateZ(-theta);
	Matrix44f m; m.MakeRotateY(phi);
	(*this)=(*this)*m;						//Roy(phi)*Roz(-theta)
	return *this;
}


//added to gxbase Matrix44f
const Matrix44f & Matrix44f::MakeRotateAboutAxis( const Vector3f& d, float cosTheta, float sinTheta){

	float a=sinTheta;
	float b=1-cosTheta;

	Vector3f u=d; u.Normalise();

	m[0][0]=1-b*(u.z()*u.z()+u.y()*u.y());    m[0][1]=-a*u.z()+b*u.x()*u.y();				m[0][2]=a*u.y()+b*u.x()*u.z();		m[0][3]=0.0f;
	m[1][0]=a*u.z()+b*u.x()*u.y();			  m[1][1]=1-b*(u.x()*u.x() + u.z()*u.z());		m[1][2]=-a*u.x()+b*u.y()*u.z();		m[1][3]=0.0f;
	m[2][0]=-a*u.y()+b*u.x()*u.z();			  m[2][1]=a*u.x()+b*u.y()*u.z();				m[2][2]=1-b*(u.x()*u.x()+u.y()*u.y());	m[2][3]=0.0f;
	m[3][0]=0.0f;							  m[3][1]=0.0f;							m[3][2]=0.0f;					m[3][3]=1.0f;

	return *this;
}

//added to gxbase Matrix44f
const Matrix44f & Matrix44f::AlignDToV ( const Vector3f& d, const Vector3f& v){
	Vector3f D=d; D.Normalise();
	Vector3f V=v; V.Normalise();
	float cosTheta=D.Dot(V);
	float sinTheta=sqrtf(1.0f-cosTheta*cosTheta);		//the angle is always between 0 and PI, so sin is positive
	if (-EPSILON<sinTheta && sinTheta<EPSILON ){
		if ( 1-EPSILON<cosTheta && cosTheta<1+EPSILON){
			//if the angle between the axis is zero, don't rotate
			Identity();					
			return *this;
		}else{
			//if the angle is PI, the cross product is zero
			Identity();
			m[0][0]=-1.0f;
			m[1][1]=-1.0f;
			m[2][2]=-1.0f;
			return *this;
		}
	}
	Vector3f n=D.Cross(V);
	MakeRotateAboutAxis(n,cosTheta,sinTheta);
	return *this;
}

//---- MakeRotate(x,y,z) -------------------------------------------------------


/**
 * Rotation matrix from unit direction vectors of axes
 * The three input vectors are assumed to be mutually orthogonal and unit length
 */

const Matrix44f & Matrix44f::MakeRotate (
   const Vector3f &x,
   const Vector3f &y,
   const Vector3f &z
) {
    // Put the three axis vectors in the top left 3x3 portion
    // of the matrix
    m[0][0]=x.x();  m[0][1]=y.x();  m[0][2]=z.x();
    m[1][0]=x.y();  m[1][1]=y.y();  m[1][2]=z.y();
    m[2][0]=x.z();  m[2][1]=y.z();  m[2][2]=z.z();

    // Rest of the matrix is just part of identity matrix
    m[0][3]=0.0;  m[1][3]=0.0;  m[2][3]=0.0;
    m[3][0]=0.0;  m[3][1]=0.0;  m[3][2]=0.0; m[3][3]=1.0;

    return *this;
}


//---- MakeRotate(angle,axis) --------------------------------------------------


/**
 * Rotation about an arbitrary axis
 */

const Matrix44f &
Matrix44f::MakeRotate ( float angle, const Vector3f & axis )
{
    // Ensure that rotation axis is unit length
    // If axis is zero length, return identity matrix (to avoid divide by zero)
    float r = axis.Length();
    if (!r) return Identity();

    // Unit direction vector of axis (x,y,z)
    float
        x = axis.x()/r,					// unit direction vector of rotation axis
        y = axis.y()/r,
        z = axis.z()/r,
        d = (float)sqrt( y*y + z*z );	// length of axis in YZ plane

    // If axis is coincident with x-axis, perform simple x-axis rotation
    if (d < 1E-3) return MakeRotateX( (x>=0.0) ? angle : -angle );

    // R = Rotation to place axis c on z-axis
    // Note: These are column vectors (ie. they appear transposed below)
    Matrix44f R;
    R.MakeRotate(
        Vector3f(  d , -x*y/d , x*z/d ),
        Vector3f(  0 ,   z/d  ,  y/d  ),
        Vector3f( -x ,   -y   ,   z   )
    );

    *this = R;                  // Rotate onto z-axis
    this->RotateZ(angle);       // Perform rotation about z-axis
    *this *= R.Transposed();    // Take out rotation Ra

    return *this;               // Return result
}//MakeRotate(angle,vector)


//---- Comparison --------------------------------------------------------------


/**
 * Exact comparison
 */

bool Matrix44f::operator == ( const Matrix44f &m2 ) const
{
    for (int r=0; r<4; r++)
        for (int c=0; c<4; c++)
            if (m[r][c] != m2[r][c]) return false;
    return true;
}


/**
 * Approximate comparison (with tolerance per term)
 */

bool Matrix44f::IsEqual ( const Matrix44f &m2, float tol ) const
{
    for (int r=0; r<4; r++)
        for (int c=0; c<4; c++)
            if (fabs(m[r][c]-m2[r][c]) > tol) return false;
    return true;
}

//------------------------------------------------------------------------------

#undef M4_AngleScale

static string subMemberString( const string & prefix, const string & field )
{
   string s = prefix ;

   if ( "" != prefix )
   {
      s += "." ;
   }

   s += field ;

   return s ;
}

// 
// 1.  Look at the constructor: getConstructor().
// 2.  Check whether it's a implicitly-defined default constructor: isDefaultConstructor(), isImplicitlyDefined().  If not, you've found your problem right there.
// 3.  Iterate over the initializers: init_begin(), init_end().
// 4.  I believe the expression for each initializer should always be a CXXConstructExpr.  Recurse.
//
void recurseOverConstructorDecls( CXXConstructorDecl * c, string subobject )
{
   for ( CXXConstructorDecl::init_iterator b = c->init_begin(), e = c->init_end() ;
         b != e ; ++b )
   {
      CXXCtorInitializer *    i        = *b ;
      FieldDecl *             f        = i->getMember() ;
      Expr *                  Init     = i->getInit() ;
      string                  subfield = subMemberString( subobject, f->getName().str() ) ;

      const QualType &        ftype    = getQualTypeForDecl( f ) ; // type of the field.  Now check if that type has a constructor.

      if ( CXXConstructExpr r = Init.getAs<CXXConstructExpr>( ) )
      {
         CXXConstructorDecl * cInner   = r.getConstructor() ;
         CXXRecordDecl *      frec     = ftype->getAsCXXRecordDecl() ;

#if 0
         if ( frec->hasDefaultConstructor() ) { cout << frec->getName().str() << " : CONSTRUCTOR: hasDefaultConstructor" << endl ; }
         if ( frec->hasConstCopyConstructor() ) { cout << frec->getName().str() << " : CONSTRUCTOR: hasConstCopyConstructor" << endl ; }
         if ( frec->hasUserDeclaredConstructor() ) { cout << frec->getName().str() << " : CONSTRUCTOR: hasUserDeclaredConstructor" << endl ; }
         if ( frec->hasUserProvidedDefaultConstructor() ) { cout << frec->getName().str() << " : CONSTRUCTOR: hasUserProvidedDefaultConstructor" << endl ; }
         if ( frec->hasUserDeclaredCopyConstructor() ) { cout << frec->getName().str() << " : CONSTRUCTOR: hasUserDeclaredCopyConstructor" << endl ; }
         if ( frec->hasCopyConstructorWithConstParam() ) { cout << frec->getName().str() << " : CONSTRUCTOR: hasCopyConstructorWithConstParam" << endl ; }
         if ( frec->hasMoveConstructor() ) { cout << frec->getName().str() << " : CONSTRUCTOR: hasMoveConstructor" << endl ; }
         if ( frec->hasTrivialDefaultConstructor() ) { cout << frec->getName().str() << " : CONSTRUCTOR: hasTrivialDefaultConstructor" << endl ; }
         if ( frec->hasNonTrivialDefaultConstructor() ) { cout << frec->getName().str() << " : CONSTRUCTOR: hasNonTrivialDefaultConstructor" << endl ; }
         if ( frec->hasConstexprDefaultConstructor() ) { cout << frec->getName().str() << " : CONSTRUCTOR: hasConstexprDefaultConstructor" << endl ; }
         if ( frec->hasTrivialCopyConstructor() ) { cout << frec->getName().str() << " : CONSTRUCTOR: hasTrivialCopyConstructor" << endl ; }
         if ( frec->hasNonTrivialCopyConstructor() ) { cout << frec->getName().str() << " : CONSTRUCTOR: hasNonTrivialCopyConstructor" << endl ; }
         if ( frec->hasUserDeclaredMoveConstructor() ) { cout << frec->getName().str() << " : CONSTRUCTOR: hasUserDeclaredMoveConstructor" << endl ; }
         if ( frec->hasFailedImplicitMoveConstructor() ) { cout << frec->getName().str() << " : CONSTRUCTOR: hasFailedImplicitMoveConstructor" << endl ; }
         if ( frec->hasConstexprNonCopyMoveConstructor() ) { cout << frec->getName().str() << " : CONSTRUCTOR: hasConstexprNonCopyMoveConstructor" << endl ; }
         if ( frec->hasTrivialMoveConstructor() ) { cout << frec->getName().str() << " : CONSTRUCTOR: hasTrivialMoveConstructor" << endl ; }
         if ( frec->hasNonTrivialMoveConstructor() ) { cout << frec->getName().str() << " : CONSTRUCTOR: hasNonTrivialMoveConstructor" << endl ; }
#endif

         if ( !cInner->isImplicitlyDefined() &&
              ( frec->hasUserDeclaredConstructor() ||
                frec->hasUserProvidedDefaultConstructor() ||
                frec->hasUserDeclaredCopyConstructor() ||
                frec->hasNonTrivialDefaultConstructor() ||
                frec->hasConstexprDefaultConstructor() ||
                frec->hasNonTrivialCopyConstructor() ||
                frec->hasUserDeclaredMoveConstructor()  ||
                frec->hasFailedImplicitMoveConstructor()  ||
                frec->hasConstexprNonCopyMoveConstructor()  ||
                frec->hasNonTrivialMoveConstructor()  ||
                //frec->hasConstCopyConstructor() ||
                //frec->hasTrivialMoveConstructor()  ||
                //frec->hasDefaultConstructor() ||
                //frec->hasCopyConstructorWithConstParam() ||
                //frec->hasMoveConstructor() ||
                //frec->hasTrivialDefaultConstructor() ||
                //frec->hasTrivialCopyConstructor() ||
                0 )
            )
         {
            cout 
               << "Global subobject requires constructor: " 
               << subfield 
               << " : " 
               << ftype.getAsString() 
               << endl ;

            recurseOverConstructorDecls( cInner, subfield ) ;
         }
      }
   }
}

bool VisitVarDecl( VarDecl * var )
{
   // modified from Eli's email "Here's the code used to implement -Wglobal-constructor:"
   Expr *         Init     = var->getInit() ;
   bool           IsGlobal = var->hasGlobalStorage() && !var->isStaticLocal() ;
   QualType       type     = var->getType();
   QualType       baseType = m_context.getBaseElementType( type ) ;

   if ( !var->getDeclContext()->isDependentContext() && Init && !Init->isValueDependent() )
   {
      if ( IsGlobal && !var->isConstexpr() &&
           !Init->isConstantInitializer( m_context, baseType->isReferenceType() ) )
      {
         if ( CXXConstructExpr r = Init.getAs<CXXConstructExpr>( ) )
         {
            CXXConstructorDecl * c = r.getConstructor() ;

            recurseOverConstructorDecls( c, var->getName().str() ) ;
         }
      }
   }

   return true ;
}

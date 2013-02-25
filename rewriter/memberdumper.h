bool myVisitFieldDecl( const string & classname, FieldDecl * f )
{
//   f = f->getDefinition() ;

   const TypeSourceInfo * pThisFieldSourceInfo = f->getTypeSourceInfo() ;
   TypeLoc thisFieldTypeLoc = pThisFieldSourceInfo->getTypeLoc() ;
   const QualType & thisFieldQualType = thisFieldTypeLoc.getType() ;

   const Type * t = thisFieldTypeLoc.getTypePtr() ;

   if ( !t->isIncompleteType() && !t->isDependentType() )
   {
      size_t szInBits = m_context.getTypeSize( thisFieldQualType ) ;
      size_t offsetInBits = m_context.getFieldOffset( f ) ;

      cout 
         << "[" << offsetInBits/8 << "]:\t" 
         << classname << "::"
         << thisFieldQualType.getAsString( m_pp ) << "\t" << f->getNameAsString()
         << "\tsize: " << szInBits/8 << endl ;
         ;
   } 

   return true ;
}

bool VisitCXXRecordDecl( CXXRecordDecl * r )
{
//   r->dump() ;
//   r = r->getDefinition() ;

   if ( r && r->getDescribedClassTemplate() )
   {
      r = r->getInstantiatedFromMemberClass() ;
   }

   if ( r && r->isThisDeclarationADefinition() )
   {
      const QualType & theMembersClassType = m_context.getRecordType( r ) ;

#if 0
      for ( CXXRecordDecl::base_class_iterator b = r->bases_begin(), e = r->bases_end() ;
            b != e ; ++b )
      {
         CXXBaseSpecifier & a = *b ;

         const QualType & q = a.getType() ;

         insertIntoMap( r->getName().str(), q ) ;
      }
#endif

      string classname = theMembersClassType.getAsString( m_pp ) ;

      for ( CXXRecordDecl::field_iterator b = r->field_begin(), e = r->field_end() ;
            b != e ; ++b )
      {
         FieldDecl * a = *b ;

         myVisitFieldDecl( classname, a ) ;
      }
   }

   return true ;
}

#ifndef ILCLIENT_IPP
#define ILCLIENT_IPP

namespace il {

inline const auto ILClient::operation() const {
  return operation_.get();
}

} // namespace il

#endif // ILCLIENT_IPP


#ifndef ILCLIENT_HPP
#define ILCLIENT_HPP

#include "iloperation_fw.hpp"
#include <memory>

namespace il {

class ILClient {
public:
  ILClient();
  virtual ~ILClient();

  void start();
  void stop();

private:
  std::unique_ptr<ILOperation> operation_;
};

} // namespace il

#include "ilclient.ipp"

#endif // ILCLIENT_HPP

